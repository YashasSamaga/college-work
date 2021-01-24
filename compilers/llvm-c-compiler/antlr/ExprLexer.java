// Generated from Expr.g4 by ANTLR 4.8
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ExprLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, T__25=26, T__26=27, T__27=28, T__28=29, T__29=30, T__30=31, 
		T__31=32, EXTERN=33, IF=34, ELSE=35, FOR=36, WHILE=37, CONTINUE=38, BREAK=39, 
		RETURN=40, SIGNED=41, UNSIGNED=42, INT=43, CHAR=44, BOOL=45, FLOAT=46, 
		VOID=47, STATIC_CAST=48, TRUE=49, FALSE=50, IDENT=51, COMMENT=52, NS=53, 
		FLOAT_LITERAL=54, INTEGER_LITERAL=55, CHARACTER_LITERAL=56, STRING_LITERAL=57;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
			"T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "T__24", 
			"T__25", "T__26", "T__27", "T__28", "T__29", "T__30", "T__31", "EXTERN", 
			"IF", "ELSE", "FOR", "WHILE", "CONTINUE", "BREAK", "RETURN", "SIGNED", 
			"UNSIGNED", "INT", "CHAR", "BOOL", "FLOAT", "VOID", "STATIC_CAST", "TRUE", 
			"FALSE", "IDENT", "COMMENT", "NS", "FLOAT_LITERAL", "INTEGER_LITERAL", 
			"CHARACTER_LITERAL", "STRING_LITERAL"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "','", "';'", "'='", "'('", "')'", "'['", "']'", "'{'", "'}'", 
			"'<'", "'>'", "'++'", "'--'", "'+'", "'-'", "'!'", "'*'", "'/'", "'%'", 
			"'<='", "'>='", "'=='", "'!='", "'&&'", "'||'", "'?'", "':'", "'*='", 
			"'/='", "'%='", "'+='", "'-='", "'extern'", "'if'", "'else'", "'for'", 
			"'while'", "'continue'", "'break'", "'return'", "'signed'", "'unsigned'", 
			"'int'", "'char'", "'bool'", "'float'", "'void'", "'static_cast'", "'true'", 
			"'false'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, "EXTERN", "IF", 
			"ELSE", "FOR", "WHILE", "CONTINUE", "BREAK", "RETURN", "SIGNED", "UNSIGNED", 
			"INT", "CHAR", "BOOL", "FLOAT", "VOID", "STATIC_CAST", "TRUE", "FALSE", 
			"IDENT", "COMMENT", "NS", "FLOAT_LITERAL", "INTEGER_LITERAL", "CHARACTER_LITERAL", 
			"STRING_LITERAL"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public ExprLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "Expr.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2;\u0184\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\3\2\3\2\3\3\3\3\3"+
		"\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\f\3"+
		"\f\3\r\3\r\3\r\3\16\3\16\3\16\3\17\3\17\3\20\3\20\3\21\3\21\3\22\3\22"+
		"\3\23\3\23\3\24\3\24\3\25\3\25\3\25\3\26\3\26\3\26\3\27\3\27\3\27\3\30"+
		"\3\30\3\30\3\31\3\31\3\31\3\32\3\32\3\32\3\33\3\33\3\34\3\34\3\35\3\35"+
		"\3\35\3\36\3\36\3\36\3\37\3\37\3\37\3 \3 \3 \3!\3!\3!\3\"\3\"\3\"\3\""+
		"\3\"\3\"\3\"\3#\3#\3#\3$\3$\3$\3$\3$\3%\3%\3%\3%\3&\3&\3&\3&\3&\3&\3\'"+
		"\3\'\3\'\3\'\3\'\3\'\3\'\3\'\3\'\3(\3(\3(\3(\3(\3(\3)\3)\3)\3)\3)\3)\3"+
		")\3*\3*\3*\3*\3*\3*\3*\3+\3+\3+\3+\3+\3+\3+\3+\3+\3,\3,\3,\3,\3-\3-\3"+
		"-\3-\3-\3.\3.\3.\3.\3.\3/\3/\3/\3/\3/\3/\3\60\3\60\3\60\3\60\3\60\3\61"+
		"\3\61\3\61\3\61\3\61\3\61\3\61\3\61\3\61\3\61\3\61\3\61\3\62\3\62\3\62"+
		"\3\62\3\62\3\63\3\63\3\63\3\63\3\63\3\63\3\64\3\64\7\64\u0134\n\64\f\64"+
		"\16\64\u0137\13\64\3\65\3\65\3\65\3\65\7\65\u013d\n\65\f\65\16\65\u0140"+
		"\13\65\3\65\3\65\3\66\6\66\u0145\n\66\r\66\16\66\u0146\3\66\3\66\3\67"+
		"\7\67\u014c\n\67\f\67\16\67\u014f\13\67\3\67\3\67\6\67\u0153\n\67\r\67"+
		"\16\67\u0154\38\58\u0158\n8\38\68\u015b\n8\r8\168\u015c\39\39\39\39\3"+
		"9\39\39\39\39\39\39\39\39\39\39\39\39\39\39\39\39\39\69\u0175\n9\r9\16"+
		"9\u0176\39\59\u017a\n9\3:\3:\7:\u017e\n:\f:\16:\u0181\13:\3:\3:\3\u017f"+
		"\2;\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35"+
		"\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\61\32\63\33\65\34\67\359\36"+
		";\37= ?!A\"C#E$G%I&K\'M(O)Q*S+U,W-Y.[/]\60_\61a\62c\63e\64g\65i\66k\67"+
		"m8o9q:s;\3\2\t\5\2C\\aac|\6\2\62;C\\aac|\4\2\f\f\17\17\4\2\13\f\"\"\3"+
		"\2\62;\3\2\60\60\3\2//\2\u0191\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t"+
		"\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2"+
		"\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2"+
		"\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2"+
		"+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2"+
		"\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2"+
		"C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3"+
		"\2\2\2\2Q\3\2\2\2\2S\3\2\2\2\2U\3\2\2\2\2W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2"+
		"\2\2]\3\2\2\2\2_\3\2\2\2\2a\3\2\2\2\2c\3\2\2\2\2e\3\2\2\2\2g\3\2\2\2\2"+
		"i\3\2\2\2\2k\3\2\2\2\2m\3\2\2\2\2o\3\2\2\2\2q\3\2\2\2\2s\3\2\2\2\3u\3"+
		"\2\2\2\5w\3\2\2\2\7y\3\2\2\2\t{\3\2\2\2\13}\3\2\2\2\r\177\3\2\2\2\17\u0081"+
		"\3\2\2\2\21\u0083\3\2\2\2\23\u0085\3\2\2\2\25\u0087\3\2\2\2\27\u0089\3"+
		"\2\2\2\31\u008b\3\2\2\2\33\u008e\3\2\2\2\35\u0091\3\2\2\2\37\u0093\3\2"+
		"\2\2!\u0095\3\2\2\2#\u0097\3\2\2\2%\u0099\3\2\2\2\'\u009b\3\2\2\2)\u009d"+
		"\3\2\2\2+\u00a0\3\2\2\2-\u00a3\3\2\2\2/\u00a6\3\2\2\2\61\u00a9\3\2\2\2"+
		"\63\u00ac\3\2\2\2\65\u00af\3\2\2\2\67\u00b1\3\2\2\29\u00b3\3\2\2\2;\u00b6"+
		"\3\2\2\2=\u00b9\3\2\2\2?\u00bc\3\2\2\2A\u00bf\3\2\2\2C\u00c2\3\2\2\2E"+
		"\u00c9\3\2\2\2G\u00cc\3\2\2\2I\u00d1\3\2\2\2K\u00d5\3\2\2\2M\u00db\3\2"+
		"\2\2O\u00e4\3\2\2\2Q\u00ea\3\2\2\2S\u00f1\3\2\2\2U\u00f8\3\2\2\2W\u0101"+
		"\3\2\2\2Y\u0105\3\2\2\2[\u010a\3\2\2\2]\u010f\3\2\2\2_\u0115\3\2\2\2a"+
		"\u011a\3\2\2\2c\u0126\3\2\2\2e\u012b\3\2\2\2g\u0131\3\2\2\2i\u0138\3\2"+
		"\2\2k\u0144\3\2\2\2m\u014d\3\2\2\2o\u0157\3\2\2\2q\u0179\3\2\2\2s\u017b"+
		"\3\2\2\2uv\7.\2\2v\4\3\2\2\2wx\7=\2\2x\6\3\2\2\2yz\7?\2\2z\b\3\2\2\2{"+
		"|\7*\2\2|\n\3\2\2\2}~\7+\2\2~\f\3\2\2\2\177\u0080\7]\2\2\u0080\16\3\2"+
		"\2\2\u0081\u0082\7_\2\2\u0082\20\3\2\2\2\u0083\u0084\7}\2\2\u0084\22\3"+
		"\2\2\2\u0085\u0086\7\177\2\2\u0086\24\3\2\2\2\u0087\u0088\7>\2\2\u0088"+
		"\26\3\2\2\2\u0089\u008a\7@\2\2\u008a\30\3\2\2\2\u008b\u008c\7-\2\2\u008c"+
		"\u008d\7-\2\2\u008d\32\3\2\2\2\u008e\u008f\7/\2\2\u008f\u0090\7/\2\2\u0090"+
		"\34\3\2\2\2\u0091\u0092\7-\2\2\u0092\36\3\2\2\2\u0093\u0094\7/\2\2\u0094"+
		" \3\2\2\2\u0095\u0096\7#\2\2\u0096\"\3\2\2\2\u0097\u0098\7,\2\2\u0098"+
		"$\3\2\2\2\u0099\u009a\7\61\2\2\u009a&\3\2\2\2\u009b\u009c\7\'\2\2\u009c"+
		"(\3\2\2\2\u009d\u009e\7>\2\2\u009e\u009f\7?\2\2\u009f*\3\2\2\2\u00a0\u00a1"+
		"\7@\2\2\u00a1\u00a2\7?\2\2\u00a2,\3\2\2\2\u00a3\u00a4\7?\2\2\u00a4\u00a5"+
		"\7?\2\2\u00a5.\3\2\2\2\u00a6\u00a7\7#\2\2\u00a7\u00a8\7?\2\2\u00a8\60"+
		"\3\2\2\2\u00a9\u00aa\7(\2\2\u00aa\u00ab\7(\2\2\u00ab\62\3\2\2\2\u00ac"+
		"\u00ad\7~\2\2\u00ad\u00ae\7~\2\2\u00ae\64\3\2\2\2\u00af\u00b0\7A\2\2\u00b0"+
		"\66\3\2\2\2\u00b1\u00b2\7<\2\2\u00b28\3\2\2\2\u00b3\u00b4\7,\2\2\u00b4"+
		"\u00b5\7?\2\2\u00b5:\3\2\2\2\u00b6\u00b7\7\61\2\2\u00b7\u00b8\7?\2\2\u00b8"+
		"<\3\2\2\2\u00b9\u00ba\7\'\2\2\u00ba\u00bb\7?\2\2\u00bb>\3\2\2\2\u00bc"+
		"\u00bd\7-\2\2\u00bd\u00be\7?\2\2\u00be@\3\2\2\2\u00bf\u00c0\7/\2\2\u00c0"+
		"\u00c1\7?\2\2\u00c1B\3\2\2\2\u00c2\u00c3\7g\2\2\u00c3\u00c4\7z\2\2\u00c4"+
		"\u00c5\7v\2\2\u00c5\u00c6\7g\2\2\u00c6\u00c7\7t\2\2\u00c7\u00c8\7p\2\2"+
		"\u00c8D\3\2\2\2\u00c9\u00ca\7k\2\2\u00ca\u00cb\7h\2\2\u00cbF\3\2\2\2\u00cc"+
		"\u00cd\7g\2\2\u00cd\u00ce\7n\2\2\u00ce\u00cf\7u\2\2\u00cf\u00d0\7g\2\2"+
		"\u00d0H\3\2\2\2\u00d1\u00d2\7h\2\2\u00d2\u00d3\7q\2\2\u00d3\u00d4\7t\2"+
		"\2\u00d4J\3\2\2\2\u00d5\u00d6\7y\2\2\u00d6\u00d7\7j\2\2\u00d7\u00d8\7"+
		"k\2\2\u00d8\u00d9\7n\2\2\u00d9\u00da\7g\2\2\u00daL\3\2\2\2\u00db\u00dc"+
		"\7e\2\2\u00dc\u00dd\7q\2\2\u00dd\u00de\7p\2\2\u00de\u00df\7v\2\2\u00df"+
		"\u00e0\7k\2\2\u00e0\u00e1\7p\2\2\u00e1\u00e2\7w\2\2\u00e2\u00e3\7g\2\2"+
		"\u00e3N\3\2\2\2\u00e4\u00e5\7d\2\2\u00e5\u00e6\7t\2\2\u00e6\u00e7\7g\2"+
		"\2\u00e7\u00e8\7c\2\2\u00e8\u00e9\7m\2\2\u00e9P\3\2\2\2\u00ea\u00eb\7"+
		"t\2\2\u00eb\u00ec\7g\2\2\u00ec\u00ed\7v\2\2\u00ed\u00ee\7w\2\2\u00ee\u00ef"+
		"\7t\2\2\u00ef\u00f0\7p\2\2\u00f0R\3\2\2\2\u00f1\u00f2\7u\2\2\u00f2\u00f3"+
		"\7k\2\2\u00f3\u00f4\7i\2\2\u00f4\u00f5\7p\2\2\u00f5\u00f6\7g\2\2\u00f6"+
		"\u00f7\7f\2\2\u00f7T\3\2\2\2\u00f8\u00f9\7w\2\2\u00f9\u00fa\7p\2\2\u00fa"+
		"\u00fb\7u\2\2\u00fb\u00fc\7k\2\2\u00fc\u00fd\7i\2\2\u00fd\u00fe\7p\2\2"+
		"\u00fe\u00ff\7g\2\2\u00ff\u0100\7f\2\2\u0100V\3\2\2\2\u0101\u0102\7k\2"+
		"\2\u0102\u0103\7p\2\2\u0103\u0104\7v\2\2\u0104X\3\2\2\2\u0105\u0106\7"+
		"e\2\2\u0106\u0107\7j\2\2\u0107\u0108\7c\2\2\u0108\u0109\7t\2\2\u0109Z"+
		"\3\2\2\2\u010a\u010b\7d\2\2\u010b\u010c\7q\2\2\u010c\u010d\7q\2\2\u010d"+
		"\u010e\7n\2\2\u010e\\\3\2\2\2\u010f\u0110\7h\2\2\u0110\u0111\7n\2\2\u0111"+
		"\u0112\7q\2\2\u0112\u0113\7c\2\2\u0113\u0114\7v\2\2\u0114^\3\2\2\2\u0115"+
		"\u0116\7x\2\2\u0116\u0117\7q\2\2\u0117\u0118\7k\2\2\u0118\u0119\7f\2\2"+
		"\u0119`\3\2\2\2\u011a\u011b\7u\2\2\u011b\u011c\7v\2\2\u011c\u011d\7c\2"+
		"\2\u011d\u011e\7v\2\2\u011e\u011f\7k\2\2\u011f\u0120\7e\2\2\u0120\u0121"+
		"\7a\2\2\u0121\u0122\7e\2\2\u0122\u0123\7c\2\2\u0123\u0124\7u\2\2\u0124"+
		"\u0125\7v\2\2\u0125b\3\2\2\2\u0126\u0127\7v\2\2\u0127\u0128\7t\2\2\u0128"+
		"\u0129\7w\2\2\u0129\u012a\7g\2\2\u012ad\3\2\2\2\u012b\u012c\7h\2\2\u012c"+
		"\u012d\7c\2\2\u012d\u012e\7n\2\2\u012e\u012f\7u\2\2\u012f\u0130\7g\2\2"+
		"\u0130f\3\2\2\2\u0131\u0135\t\2\2\2\u0132\u0134\t\3\2\2\u0133\u0132\3"+
		"\2\2\2\u0134\u0137\3\2\2\2\u0135\u0133\3\2\2\2\u0135\u0136\3\2\2\2\u0136"+
		"h\3\2\2\2\u0137\u0135\3\2\2\2\u0138\u0139\7\61\2\2\u0139\u013a\7\61\2"+
		"\2\u013a\u013e\3\2\2\2\u013b\u013d\n\4\2\2\u013c\u013b\3\2\2\2\u013d\u0140"+
		"\3\2\2\2\u013e\u013c\3\2\2\2\u013e\u013f\3\2\2\2\u013f\u0141\3\2\2\2\u0140"+
		"\u013e\3\2\2\2\u0141\u0142\b\65\2\2\u0142j\3\2\2\2\u0143\u0145\t\5\2\2"+
		"\u0144\u0143\3\2\2\2\u0145\u0146\3\2\2\2\u0146\u0144\3\2\2\2\u0146\u0147"+
		"\3\2\2\2\u0147\u0148\3\2\2\2\u0148\u0149\b\66\2\2\u0149l\3\2\2\2\u014a"+
		"\u014c\t\6\2\2\u014b\u014a\3\2\2\2\u014c\u014f\3\2\2\2\u014d\u014b\3\2"+
		"\2\2\u014d\u014e\3\2\2\2\u014e\u0150\3\2\2\2\u014f\u014d\3\2\2\2\u0150"+
		"\u0152\t\7\2\2\u0151\u0153\t\6\2\2\u0152\u0151\3\2\2\2\u0153\u0154\3\2"+
		"\2\2\u0154\u0152\3\2\2\2\u0154\u0155\3\2\2\2\u0155n\3\2\2\2\u0156\u0158"+
		"\t\b\2\2\u0157\u0156\3\2\2\2\u0157\u0158\3\2\2\2\u0158\u015a\3\2\2\2\u0159"+
		"\u015b\t\6\2\2\u015a\u0159\3\2\2\2\u015b\u015c\3\2\2\2\u015c\u015a\3\2"+
		"\2\2\u015c\u015d\3\2\2\2\u015dp\3\2\2\2\u015e\u015f\7)\2\2\u015f\u0160"+
		"\13\2\2\2\u0160\u017a\7)\2\2\u0161\u0162\7)\2\2\u0162\u0163\7^\2\2\u0163"+
		"\u0164\7p\2\2\u0164\u017a\7)\2\2\u0165\u0166\7)\2\2\u0166\u0167\7^\2\2"+
		"\u0167\u0168\7$\2\2\u0168\u017a\7)\2\2\u0169\u016a\7)\2\2\u016a\u016b"+
		"\7^\2\2\u016b\u016c\7^\2\2\u016c\u017a\7)\2\2\u016d\u016e\7)\2\2\u016e"+
		"\u016f\7^\2\2\u016f\u0170\7)\2\2\u0170\u017a\7)\2\2\u0171\u0172\7)\2\2"+
		"\u0172\u0174\7^\2\2\u0173\u0175\t\6\2\2\u0174\u0173\3\2\2\2\u0175\u0176"+
		"\3\2\2\2\u0176\u0174\3\2\2\2\u0176\u0177\3\2\2\2\u0177\u0178\3\2\2\2\u0178"+
		"\u017a\7)\2\2\u0179\u015e\3\2\2\2\u0179\u0161\3\2\2\2\u0179\u0165\3\2"+
		"\2\2\u0179\u0169\3\2\2\2\u0179\u016d\3\2\2\2\u0179\u0171\3\2\2\2\u017a"+
		"r\3\2\2\2\u017b\u017f\7$\2\2\u017c\u017e\13\2\2\2\u017d\u017c\3\2\2\2"+
		"\u017e\u0181\3\2\2\2\u017f\u0180\3\2\2\2\u017f\u017d\3\2\2\2\u0180\u0182"+
		"\3\2\2\2\u0181\u017f\3\2\2\2\u0182\u0183\7$\2\2\u0183t\3\2\2\2\r\2\u0135"+
		"\u013e\u0146\u014d\u0154\u0157\u015c\u0176\u0179\u017f\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}