from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    
    a_lst = a.split('\n')
    b_lst = b.split('\n')
    lst = a_lst if len(a_lst) > len(b_lst) else b_lst
    common_set = set()
    for line in lst:
        if line in a_lst and line in b_lst:
            common_set.add(line)
    return list(common_set)

def sentences(a, b):
    """Return sentences in both a and b"""

    a_set = set(sent_tokenize(a))
    b_set = set(sent_tokenize(b))
    full = set()
    full.update(a_set)
    full.update(b_set)
    common_set = set()
    for sentence in full:
        if sentence in a_set and sentence in b_set:
            common_set.add(sentence)
    return list(common_set)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    substr_a = set()
    for i in range(len(a) - n - 1):
        substr_a.add(a[i:i+n])
    substr_b = set()
    for i in range(len(b) - n - 1):
        substr_b.add(b[i:i-n-1])
    full = set()
    full.update(substr_a)
    full.update(substr_b)
    common_substr = set()
    for sub in full:
        if sub in substr_a and sub in substr_b:
            common_substr.add(sub)
    return list(common_substr)
