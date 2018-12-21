# Configuration
sequenceFile = "sequence.fasta" # sequence must be in 5' to 3'
intronFile = "Introns.csv"
nucleotides = ['A', 'T', 'G', 'C']
complements = { 'A' : 'T', 'T' : 'A', 'G' : 'C', 'C' : 'G', 'X' : 'X' }

# taken from https://pythonforbiologists.com/dictionaries/
genetic_code = {
    'ATA':'I', 'ATC':'I', 'ATT':'I', 'ATG':'M',
    'ACA':'T', 'ACC':'T', 'ACG':'T', 'ACT':'T',
    'AAC':'N', 'AAT':'N', 'AAA':'K', 'AAG':'K',
    'AGC':'S', 'AGT':'S', 'AGA':'R', 'AGG':'R',
    'CTA':'L', 'CTC':'L', 'CTG':'L', 'CTT':'L',
    'CCA':'P', 'CCC':'P', 'CCG':'P', 'CCT':'P',
    'CAC':'H', 'CAT':'H', 'CAA':'Q', 'CAG':'Q',
    'CGA':'R', 'CGC':'R', 'CGG':'R', 'CGT':'R',
    'GTA':'V', 'GTC':'V', 'GTG':'V', 'GTT':'V',
    'GCA':'A', 'GCC':'A', 'GCG':'A', 'GCT':'A',
    'GAC':'D', 'GAT':'D', 'GAA':'E', 'GAG':'E',
    'GGA':'G', 'GGC':'G', 'GGG':'G', 'GGT':'G',
    'TCA':'S', 'TCC':'S', 'TCG':'S', 'TCT':'S',
    'TTC':'F', 'TTT':'F', 'TTA':'L', 'TTG':'L',
    'TAC':'Y', 'TAT':'Y', 'TAA':'_', 'TAG':'_',
    'TGC':'C', 'TGT':'C', 'TGA':'_', 'TGG':'W'
	}

start_codons = [ "ATG" ]
stop_codons = [ "TAG", "TAA", "TGA" ]

primer_end = ['C', 'A']

# Implementation
# Utility functions
def dump_sequence(outFile, sequence, npl = 70):
	for j in range(0, len(sequence), npl):
		outFile.write(''.join(sequence[j : j + npl]) + '\n')
	outFile.write('\n')

def dump_protein(outFile, sequence, start, stop, npl = 70):
	count = 0
	codon_i = 0
	codon = ['X', 'X', 'X']
	for i in range(start, stop + 2): 
		N = sequence[i]
		if N != 'X':
			codon[codon_i] = N
			codon_i += 1
		if codon_i == 3:
			codon_i = 0
			count += 1
			outFile.write(genetic_code[''.join(codon)])
			if count == 70:
				count = 0
				outFile.write('\n')
			
	outFile.write('\n')

def get_longest_protein(sequence, offset = 0):
	start = -1
	stop = -1

	codon_i = (3 - offset)%3
	codon = ['X', 'X', 'X']
	for start in range(0, len(sequence)): 
		N = sequence[start]
		if N != 'X':
			codon[codon_i] = N
			codon_i += 1
			
		if codon_i == 3:
			codon_i = 0	
			if ''.join(codon) in start_codons:
				break
	
	count = 0	
	for stop in range(start + 1, len(sequence)): 
		N = sequence[stop]
		if N != 'X':
			codon[codon_i] = N
			codon_i += 1
			
		if codon_i == 3:
			codon_i = 0
			count += 1
			if ''.join(codon) in stop_codons:
				break
	return tuple([start - 2, stop - 2, count - 1])

def calculate_gc_content(primer):
	count_G = primer.count('G')
	count_C = primer.count('C')
	return (count_G + count_C)/len(primer)

def calculate_tm(primer):
	count_A = primer.count('A')
	count_T = primer.count('T')
	count_G = primer.count('G')
	count_C = primer.count('C')
	return 4*(count_G + count_C) + 2*(count_A + count_T)

def longest_selfcompl_sequence(sequence):
    maxLength = 1

    start = 0
    length = len(sequence)

    low = 0
    high = 0

    for i in range(1, length):
        low = i - 1
        high = i
        while low >= 0 and high < length and sequence[low] == complements[sequence[high]]:
            if high - low + 1 > maxLength:
                start = low
                maxLength = high - low + 1
            low -= 1
            high += 1

        low = i - 1
        high = i + 1
        while low >= 0 and high < length and sequence[low] == complements[sequence[high]]:
            if high - low + 1 > maxLength:
                start = low
                maxLength = high - low + 1
            low -= 1
            high += 1

    return maxLength

# set primer error tolerance in this function
def performance_measure(primer):
	rating = 100
	
	# off by one costs 4 points
	if len(primer) < 20:
		rating -= (20 - len(primer)) * 4
		
	if len(primer) > 35:
		rating -= (len(primer) - 35) * 4
	
	# does not end with 'primer_end' costs a ton
	if primer[-1] not in primer_end:
		rating -= 50
	
	# each difference costs 1
	# try to retain temperatures near 65
	tm = calculate_tm(primer)
	if tm < 63:
		rating -= 63 - tm
	if tm > 67:
		rating -= tm - 67
	
	# double the cost for going outside 60-70 limits
	if tm < 60:
		rating -= 60 - tm
	if tm > 70:
		rating -= tm - 70
	
	# repeating patterns - cost 2*n for consecutive series of 'n' nucleotides if n > 2 
	prev = 'X'
	cnt = 0
	for N in primer:
		if N == prev:
			cnt += 1
		else:
			if cnt > 2:
				rating -= cnt*2
			cnt = 0
			prev = N
	
	# self complementary sequences
	lscs = longest_selfcompl_sequence(primer)
	if lscs > 5:
		rating -= lscs * 3
	
	# each 0.01 difference costs 3
	gc_content = calculate_gc_content(primer)
	if gc_content < 0.4:
		rating -= (0.4 - gc_content) * 300
	if gc_content > 0.6:
		rating -= (gc_content - 0.6) * 300
		
	return rating

def generate_primer(orf, startp):
	tolerance_level = 100 # 100 = fullfills all conditions

	primer_list = [['X'] * 20]
	sorting = [(0, 0)] # rating, index
	perfect_count = 0
	
	for start in range(0, startp, 1):			
		for base_len in range(18, 40, 1): 
			forward_primer = orf[start:start + base_len]
			
			if forward_primer not in primer_list:
				new_rating = performance_measure(forward_primer)
				perfect_count += (new_rating >= tolerance_level)
				sorting.append(tuple([new_rating, len(primer_list)]))
				primer_list.append(forward_primer)		
			
			if forward_primer[-1] not in primer_end:
				for i in range(start + base_len, len(orf)):
					forward_primer.append(orf[i])
					if forward_primer[-1] in primer_end:
						break		
				
			gc_content = calculate_gc_content(forward_primer)
			tm = calculate_tm(forward_primer)
			start_tm = start
			while tm < 60:
				start_tm -= 1
				if start < 0:
					break
					
				forward_primer = [orf[start_tm]] + forward_primer
				tm = calculate_tm(forward_primer)
				
				if forward_primer not in primer_list:
					new_rating = performance_measure(forward_primer)
					perfect_count += (new_rating >= tolerance_level)
					sorting.append(tuple([new_rating, len(primer_list)]))
					primer_list.append(forward_primer)		
				
			if forward_primer not in primer_list:
				new_rating = performance_measure(forward_primer)
				perfect_count += (new_rating >= tolerance_level)
				sorting.append(tuple([new_rating, len(primer_list)]))
				primer_list.append(forward_primer)
	
			if perfect_count >= 3:
				break
				
		if perfect_count >= 3:
				break		
	
	return tuple([sorted(sorting), primer_list])
	
# main
def main():
	print("Please change the value of 'tolerance_level' in 'generate_primer' to make the program execute faster")

	title = ""
	sequence = []
	complementary_sequence = []
	
	exonic_sequence_X = []
	exonic_sequence = []
	exonic_complementary_sequence = []
	exonic_complementary_sequence_X = []
	
	reading_frames = {}
	exonic_reading_frames = {}
	
	exonic_reading_frames_codons = {}
	
	with open(sequenceFile, "r") as inFile:
		title = inFile.readline()
		while not title.strip():
			title = inFile.readline()
		
		for line in inFile:
			sequence += [char for char in list(line.strip()) if char in nucleotides]
			
		complementary_sequence = [complements[char] for char in reversed(sequence)]
		
		for i in range(0, 3):
			reading_frames[i] = sequence[i:]
			
		for i in range(0, 3):
			reading_frames[i+3] = complementary_sequence[i:]
			
	with open(intronFile, "r") as inFile:
		exonic_sequence = list(sequence)
		exonic_sequence_X = list(sequence)
		inFile.readline()
		introns = []
		for line in inFile:
			if line.strip() != '':
				fields = line.strip().split(',')
				introns.append(tuple([int(fields[0]) - 1, int(fields[1])]))

		offset = 0
		for intron in sorted(introns):
			start, end = intron[0], intron[1]
			exonic_sequence_X[start:end] = ['X'] * (end - start)
			del exonic_sequence[start - offset : end - offset]
			offset += end - start			
		
		exonic_complementary_sequence = [complements[char] for char in reversed(exonic_sequence)]
		exonic_complementary_sequence_X = [complements[char] for char in reversed(exonic_sequence_X)]
		
		for i in range(0, 3):
			exonic_reading_frames[i] = exonic_sequence[i:]
			
		for i in range(0, 3):
			exonic_reading_frames[i + 3] = exonic_complementary_sequence[i:]
			
		for i in range(0,6):
			frame = exonic_reading_frames[i]
			exonic_reading_frames_codons[i] = []
			for j in range(0, len(frame), 3):
				exonic_reading_frames_codons[i].append(''.join(frame[j:j+3]))

	with open("output/1.txt", "w") as outFile:
		for i in range(0, 3):
			outFile.write("> Reading Frame " + str(i + 1) + "\n")	
			dump_sequence(outFile, reading_frames[i])		
			
		for i in range(0, 3):
			outFile.write("> Reading Frame " + str(i + 4) + "\n")	
			dump_sequence(outFile, reading_frames[i + 3])
	
	orf_start = -1
	orf_stop = -1
	orf_count = -1
	orf_frame = -1
	for i in range(0, 3):
		start, stop, count = get_longest_protein(exonic_sequence_X, i)
		if count > orf_count:
			orf_start = start
			orf_stop = stop
			orf_count = count
			orf_frame = i
		
	for i in range(0, 3):	
		start, stop, count = get_longest_protein(exonic_complementary_sequence_X, i)
		if count > orf_count:
			orf_start = start
			orf_stop = stop
			orf_count = count
			orf_frame = i + 3
	
	orf_cstop = len(sequence) - (orf_start + 2) - 1
	orf_cstart = len(sequence) - (orf_stop + 2) - 1
		
	with open("output/2.txt", "w") as outFile:
		outFile.write("> Reading Frame " + str(orf_frame + 1) + "\n")
		dump_sequence(outFile, reading_frames[orf_frame])
			
	with open("output/3.txt", "w") as outFile:
		outFile.write("> Protein Sequence\n")
		if orf_frame < 3:
			orf = exonic_sequence_X
		else:
			orf = exonic_complementary_sequence_X
		dump_protein(outFile, orf, orf_start, orf_stop)
		
	with open("output/4.txt", "w") as outFile:
		if orf_frame < 3:
			orf = sequence
			orf_comp = complementary_sequence
		else:
			orf = complementary_sequence
			orf_comp = sequence
		
		forward_primers = [[], [], []]
		ret = generate_primer(orf, orf_start)
		primer_list = ret[1]
		primer_ranks = ret[0]
		
		forward_primers[0] = primer_list[primer_ranks[-1][1]]
		forward_primers[1] = primer_list[primer_ranks[-2][1]]
		forward_primers[2] = primer_list[primer_ranks[-3][1]]
		
		reverse_primers = [[], [], []]
		ret = generate_primer(orf_comp, orf_cstart)
		primer_list = ret[1]
		primer_ranks = ret[0]
		
		reverse_primers[0] = primer_list[primer_ranks[-1][1]]
		reverse_primers[1] = primer_list[primer_ranks[-2][1]]
		reverse_primers[2] = primer_list[primer_ranks[-3][1]]
		
		for i in range(0, 3):
			outFile.write("Forward Primer - " + ''.join(forward_primers[i]))
			outFile.write("\tTm(in deg C) - " + str(calculate_tm(forward_primers[i])) + '\n')
			outFile.write("Reverse Primer - " + ''.join(reverse_primers[i]))
			outFile.write("\tTm(in deg C) - " + str(calculate_tm(reverse_primers[i])))
			outFile.write("\n\n")	
		
	with open("output/5.txt", "w") as outFile:
		outFile.write("> E.coli cloning sequence\n")
		dump_sequence(outFile, exonic_reading_frames[orf_frame])
		outFile.write("> Pichia pastoris cloning sequence\n")
		dump_sequence(outFile, sequence)
		outFile.write("> HEK293 cloning sequence\n")
		dump_sequence(outFile, sequence)
		
if __name__ == "__main__":
	main()

