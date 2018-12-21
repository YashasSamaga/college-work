#written for Python 3.6
import numpy as np
import math

#*********************************************************#
# PDB Parser
class PDBParser:
	def __parse_COMPND(self, line): # space already trimmed in fields
		fields = line.split()[2:]
		fields = ''.join(fields).split(':')
		if fields[0] == "CHAIN":
			self.chains.append(fields[1].replace(';', '').split(','))

	def __parse_TITLE(self, line):
		self.title = line[10:].strip()

	def __parse_SEQRES(self, line):
		fields = line[19:].split()
		self.sequence.extend(fields)

	def __parse_HET(self, line):
		self.hetero.add(line[7:11].strip())

	def __parse_ATOM(self, line): # assumes input is in order
		atom = line[12:17].strip()
		if atom == "N" or atom == "C" or atom == "CA":
			cid = ''
			for chain in self.chains:
				if line[21] in chain:
					cid = chain[0]

			if cid not in self.atoms:
				self.atoms[cid] = []

			assert(cid != '') #the atom must belong to some chain

			x = float(line[30:39])
			y = float(line[38:47])
			z = float(line[46:55])
			self.atoms[cid].append([atom, np.array([x, y, z])])

	def __init__(self, inputFile):
		self.sequence = []
		self.hetero = set([])
		self.chains = []
		self.atoms = {} #dictionary of chains

		parser_func_map = {
			"TITLE" : self.__parse_TITLE,
			"COMPND" : self.__parse_COMPND,
			"SEQRES" : self.__parse_SEQRES,
			"HET"	: self.__parse_HET,
			"ATOM" : self.__parse_ATOM
		}

		inFile = open(inputFile, "r")		
		for line in inFile:
			fields = line.split()
			if len(fields) and parser_func_map.get(fields[0]) != None:
				parser_func_map[fields[0]](line)
		inFile.close()
		self.chains.sort()

#*********************************************************#
# main
input_filename = input()
output_filename = input_filename.split('.')[0] + "_output.txt"

pdb = PDBParser(input_filename)

outFile = open(output_filename, "w") # TODO: handle failure

# print title
outFile.write(pdb.title + '\n')

# print length of the protien
pdb.length = len(pdb.sequence)
outFile.write("LENGTH" + '\t' + str(pdb.length) + '\n')

# print number of chains and their names
total = []
for lst in pdb.chains:
	total += lst

# NOTE: combines all identifiers (including multiple) and prints them in sorted order
outFile.write("CHAIN" + '\t' + str(len(pdb.chains)) + '\t' + ','.join(sorted(total)) + '\n')

# number of different known amino acids by fraction
AAFreq = {}
for amino_acid in pdb.sequence:
	if amino_acid not in AAFreq:
		AAFreq[amino_acid] = 0
	AAFreq[amino_acid] += 1

for amino_acid, freq in sorted(AAFreq.items()):
	outFile.write(amino_acid + '\t' + str(freq/pdb.length) + '\n')

# number of unknown amino acids
unknown_amino_acids = 0
if 'UNK' in AAFreq:
	unknown_amino_acids = AAFreq['UNK']
outFile.write("UNKNOWN" + '\t' + str(unknown_amino_acids) + '\n')

# number of ligand molecules and their names
pdb.hetero.discard("H2O")
if len(pdb.hetero) > 0:
	outFile.write("LIGANDS" + '\t' + ','.join(sorted(pdb.hetero)) + '\n')

# calculate dihedral angles for each chain
for chain_id, chain in sorted(pdb.atoms.items()):
	outFile.write("CHAIN-" + chain_id)
	prevAtom = []

	# calculate dihedral angles for the current chain
	for i in range(0, len(chain)):
		if i % 3 == 0:
			outFile.write('\n')
		if i == 0 or i + 2 >= len(chain):
			outFile.write("NA\t")		
		else:
			curAtom = chain[i]
			nextAtom1 = chain[i+1]
			nextAtom2 = chain[i+2]

			atom1_posVec = prevAtom[1]
			atom2_posVec = curAtom[1]
			atom3_posVec = nextAtom1[1]
			atom4_posVec = nextAtom2[1]

			# Plane A : atom1_posVec - atom2_posVec - atom3_posVec
			normal_A = np.cross(atom2_posVec - atom1_posVec, atom3_posVec - atom1_posVec)

			# Plane B : atom2_posVec - atom3_posVec - atom4_posVec
			normal_B = np.cross(atom3_posVec - atom2_posVec, atom4_posVec - atom2_posVec)

			bond_line = (atom3_posVec - atom2_posVec) / (np.linalg.norm(atom3_posVec - atom2_posVec));
			orthogonal = np.cross(bond_line, normal_B)			

			angle = math.atan2(np.dot(normal_A, orthogonal), np.dot(normal_A, normal_B))
			outFile.write(str(np.round(np.degrees(angle), 3))  + '\t')
		prevAtom = chain[i]
	outFile.write('\n')
