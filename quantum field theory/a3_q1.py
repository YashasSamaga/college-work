from ast import Num
from enum import Enum, unique, auto
from typing import OrderedDict

@unique
class TermType(Enum):
    ZJ0 = auto()       # exp(-i/2 ...)
    DF0 = auto()       # DF(0)
    DFX1X2 = auto()    # Int(DF(x1 - x2)J(x)d4x)

@unique
class OperatorType(Enum):
    ADD = auto()
    MULTIPLY = auto()

class Expression:
    def __str__(self):
        raise NotImplementedError

def getExprRank(expr):
    if isinstance(expr, NumericLiteral):
        return 0
    if isinstance(expr, PowerExpression):
        return getExprRank(expr.expr)
    if isinstance(expr, AtomicTerm):
        if expr.type == TermType.DF0:
            return 10
        if expr.type == TermType.DFX1X2:
            return 11
        if expr.type == TermType.ZJ0:
            return 12
    if isinstance(expr, MultiplyExpression):
        return 20
    if isinstance(expr, AddExpression):
        return 30
    return 40        

class CommutativeAssociativeExpression(Expression):
    def __init__(self, exprs, op):
        assert(isinstance(exprs, list))
        assert(all(issubclass(type(e), Expression) for e in exprs))
        self.exprs = exprs
        self.op = op

    def add(self, e):
        self.exprs.append(e)

    def sort(self):
        self.exprs = sorted(self.exprs, key= lambda x : getExprRank(x))

class AddExpression(CommutativeAssociativeExpression):
    def __init__(self, exprs):
        super(AddExpression, self).__init__(exprs, OperatorType.ADD)

    def __str__(self):
        return '(' + " + ".join([str(e) for e in self.exprs]) + ')'

    def __eq__(self, other):
        if len(self.exprs) != len(other.exprs):
            return False
        return sorted(self.exprs) == sorted(other.exprs)
    
    def __hash__(self):
        return 12345 + len(self.exprs)

class MultiplyExpression(CommutativeAssociativeExpression):
    def __init__(self, exprs):
        super(MultiplyExpression, self).__init__(exprs, OperatorType.MULTIPLY)

    def __str__(self):
        return '(' + " * ".join([str(e) for e in self.exprs]) + ')'

    def __eq__(self, other):
        if len(self.exprs) != len(other.exprs):
            return False
        from collections import Counter
        return Counter(self.exprs) == Counter(other.exprs)

    def __hash__(self):
        return 54321 + len(self.exprs)

class PowerExpression(Expression):
    def __init__(self, expr, power):
        assert(issubclass(type(expr), Expression))
        self.expr = expr
        self.power = power

    def __str__(self):
        return str(self.expr) + '^' + str(self.power)

    def __eq__(self, other):
        return self.expr == other.expr and self.power == other.power

    def __hash__(self):
        return hash(type(self.expr)) + hash(self.power)

class AtomicTerm(Expression):
    def __init__(self, type):
        assert(type in TermType)
        self.type = type

    def __str__(self):
        mapping = {
            TermType.ZJ0 : "E",
            TermType.DF0 : "DF(0)",
            TermType.DFX1X2 : "Int[DF(x1 - x2)J(x)d4x]"
        }
        return str(mapping[self.type])

    def __eq__(self, other):
        return self.type == other.type

    def __hash__(self):
        return hash(self.type)

class NumericLiteral(Expression):
    def __init__(self, value):
        self.value = value

    def normalize(self):
        if isinstance(self.value, complex):
            r, i = self.value.real, self.value.imag
            if r == -0.0:
                r = 0
            if i == -0.0:
                i = 0.0
            if isinstance(r, float) and float.is_integer(r):
                r = int(r)
            if isinstance(i, float) and float.is_integer(i):
                i = int(i)
            self.value = complex(r, i) if i != 0.0 else r

    def __str__(self):
        self.normalize()
        return str(self.value)

    def __eq__(self, other):
        return self.value == other.value

    def __hash__(self):
        return hash(self.value)

current = AtomicTerm(TermType.ZJ0)

def reorder_expr(expr):
    if isinstance(expr, AddExpression):
        expr.sort()
    if isinstance(expr, MultiplyExpression):
        expr.sort()
    return expr

def merge_terms(expr):
    if isinstance(expr, AddExpression):
        subexprs = [merge_terms(e) for e in expr.exprs]

        term_counts = {}
        for e in subexprs:
            if isinstance(e, MultiplyExpression):
                ct = sum(1 for x in e.exprs if isinstance(x, NumericLiteral))
                if ct == 1 and isinstance(e.exprs[0], NumericLiteral) and len(e.exprs) > 1:
                    coeff = e.exprs[0].value
                    residual = MultiplyExpression(e.exprs[1:])
                    if residual not in term_counts:
                        term_counts[residual] = 0
                    term_counts[residual] += coeff
                    continue

            if e not in term_counts:
                term_counts[e] = 0
            term_counts[e] += 1

        newexprs = []
        for k, v in term_counts.items():
            if v == 1:
                newexprs.append(k)
            else:
                newexprs.append(MultiplyExpression([NumericLiteral(v), k]))
        return AddExpression(newexprs)

    if isinstance(expr, MultiplyExpression):
        subexprs = [merge_terms(e) for e in expr.exprs]

        term_counts = {}
        for e in subexprs:
            if isinstance(e, PowerExpression):
                base, exp = e.expr, e.power
                if base not in term_counts:
                    term_counts[base] = 0
                term_counts[base] += exp
                continue

            if e not in term_counts:
                term_counts[e] = 0
            term_counts[e] += 1

        newexprs = []
        for k, v in term_counts.items():
            if v == 1:
                newexprs.append(k)
            else:
                newexprs.append(PowerExpression(k, v))
        return MultiplyExpression(newexprs)

    return expr

def distribute_expr(expr):
    if isinstance(expr, MultiplyExpression):
        subexprs = expr.exprs
        for i in range(len(subexprs)):
            if isinstance(subexprs[i], AddExpression):
                add_subexprs = subexprs[i].exprs
                new_subexprs = []
                for j in range(len(add_subexprs)):
                    import copy
                    multi_subexpr = copy.deepcopy(subexprs)
                    multi_subexpr[i] = add_subexprs[j]
                    new_subexprs.append(MultiplyExpression(multi_subexpr))
                return distribute_expr(AddExpression(new_subexprs))
    return expr

def optimize_expr(expr):
    expr = distribute_expr(expr)
    expr = reorder_expr(expr)
    if isinstance(expr, AddExpression):
        subexprs = [optimize_expr(reorder_expr(e)) for e in expr.exprs]

        subexprs_nonadd = [e for e in subexprs if not isinstance(e, AddExpression)]
        subexprs_add = [e.exprs for e in subexprs if isinstance(e, AddExpression)]
        subexprs = subexprs_nonadd
        for s in subexprs_add:
            subexprs += s

        subexprs = AddExpression(subexprs)
        subexprs.sort()
        subexprs = subexprs.exprs

        initial_literal = 0
        for e in subexprs:
            if isinstance(e, NumericLiteral):
                initial_literal += e.value
        
        subexprs_non_literal = [e for e in subexprs if not isinstance(e, NumericLiteral)]
        if not subexprs_non_literal:
            return NumericLiteral(initial_literal)
        
        subexprs = subexprs_non_literal
        if initial_literal:
            subexprs = [initial_literal] + subexprs

        newexpr = AddExpression(subexprs)
        if len(newexpr.exprs) == 1:
            return newexpr.exprs[0]
        return newexpr

    if isinstance(expr, MultiplyExpression):
        subexprs = [optimize_expr(reorder_expr(e)) for e in expr.exprs]

        subexprs_nonmult = [e for e in subexprs if not isinstance(e, MultiplyExpression)]
        subexprs_mult = [e for e in subexprs if isinstance(e, MultiplyExpression)]
        subexprs = subexprs_nonmult
        for s in subexprs_mult:
            subexprs += s.exprs

        subexprs = MultiplyExpression(subexprs)
        subexprs.sort()
        subexprs = subexprs.exprs

        initial_literal = 1
        atomicTerms_count = {}
        for e in subexprs:
            if isinstance(e, NumericLiteral):
                initial_literal *= e.value
            if isinstance(e, AtomicTerm):
                if e.type not in atomicTerms_count:
                    atomicTerms_count[e.type] = 0
                atomicTerms_count[e.type] += 1
            assert(not isinstance(e, MultiplyExpression))

        newexpr_list = []
        if initial_literal == 0:
            return NumericLiteral(0)
        elif initial_literal != 1:
            newexpr_list.append(NumericLiteral(initial_literal))

        for k, v in atomicTerms_count.items():
            if v == 1:
                newexpr_list.append(AtomicTerm(k))
            elif v > 1:
                newexpr_list.append(PowerExpression(AtomicTerm(k), v))

        newexpr_list += [e for e in subexprs if (not isinstance(e, NumericLiteral) and not isinstance(e, AtomicTerm))]
        if len(newexpr_list) == 1:
            return newexpr_list[0]
        return MultiplyExpression(newexpr_list)

    if isinstance(expr, PowerExpression):
        if expr.power == 0:
            return NumericLiteral(1)
        if expr.power == 1:
            return expr.expr
    return expr   

def diff_wrapper(expr):
    return MultiplyExpression([NumericLiteral(-1j), diff(expr)])

def diff(expr):
    if isinstance(expr, AddExpression):
        return AddExpression([diff(e) for e in expr.exprs])
    if isinstance(expr, MultiplyExpression):
        subexprs = expr.exprs
        product_terms = []
        for i in range(len(subexprs)):
            import copy
            temp = copy.deepcopy(subexprs)
            temp[i] = diff(temp[i])
            product_terms.append(MultiplyExpression(temp))
        return AddExpression(product_terms)
    if isinstance(expr, PowerExpression):
        return MultiplyExpression(
            [
                NumericLiteral(expr.power),
                PowerExpression(expr.expr, expr.power - 1),
                diff(expr.expr)
            ]
        )

    if isinstance(expr, AtomicTerm):
        if expr.type == TermType.ZJ0:
            return MultiplyExpression(
                    [
                        NumericLiteral(-1j),
                        AtomicTerm(TermType.DFX1X2),
                        AtomicTerm(TermType.ZJ0)
                    ]
                )
        if expr.type == TermType.DF0:
            return NumericLiteral(0)
        if expr.type == TermType.DFX1X2:
            return AtomicTerm(TermType.DF0)

    if isinstance(expr, NumericLiteral):
        return NumericLiteral(0)

    print(expr)
    assert(0)

def prepare(expr):
    expr = distribute_expr(expr)
    expr = optimize_expr(expr)
    expr = distribute_expr(expr)
    expr = optimize_expr(expr)
    expr = distribute_expr(expr)
    expr = optimize_expr(expr)
    expr = distribute_expr(expr)
    expr = optimize_expr(expr)
    expr = merge_terms(expr)
    return expr

print(current, "\n")
derivative1 = prepare(diff_wrapper(current))
print("Derivative1:\n", derivative1, "\n\n")

derivative2 = prepare(diff_wrapper(derivative1))
print("Derivative2:\n", derivative2, "\n\n")


derivative3 = prepare(diff_wrapper(derivative2))
print("Derivative3:\n", derivative3, "\n\n")

derivative4 = prepare(diff_wrapper(derivative3))
print("Derivative4:\n", derivative4, "\n\n")

derivative5 = prepare(diff_wrapper(derivative4))
print("Derivative5:\n", derivative5, "\n\n")

derivative6 = prepare(diff_wrapper(derivative5))
print("Derivative6:\n", derivative6, "\n\n")

derivative7 = prepare(diff_wrapper(derivative6))
print("Derivative7:\n", derivative7, "\n\n")

derivative8 = prepare(diff_wrapper(derivative7))
print("Derivative8:\n", derivative8, "\n\n")

