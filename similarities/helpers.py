from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    
    a_lst = set(a.split('\n'))
    b_lst = set(b.split('\n'))
    return list(a_lst.intersection(b_lst))

def sentences(a, b):
    """Return sentences in both a and b"""

    a_set = set(sent_tokenize(a))
    b_set = set(sent_tokenize(b))
    return list(a_set.intersection(b_set))


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    
    substr_a = set()
    for i in range(len(a) - n + 1):
        substr_a.add(a[i:i+n])
    substr_b = set()
    for i in range(len(b) - n + 1):
        substr_b.add(b[i:i+n])
    return list(substr_a.intersection(substr_b))
