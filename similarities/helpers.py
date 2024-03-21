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
    a_set.update(b_set)
    return list(a_set)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # TODO
    return []
