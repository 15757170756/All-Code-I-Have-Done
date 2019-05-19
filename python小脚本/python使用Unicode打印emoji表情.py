def unicode_test(value):
    import unicodedata
    name = unicodedata.name(value)
    value2 = unicodedata.lookup(name)
    print('value="%s", name="%s", value2="%s"' % (value, name, value2))

unicode_test('A')
unicode_test('$')
unicode_test('\u20ac')
unicode_test('\u2603')
unicode_test('\u2602')
unicode_test('\u2615')
unicode_test('\u00e9')
for i in range(0, 10):
    pass
place = 'café'
print(place)
print('caf\N{LATIN SMALL LETTER E WITH ACUTE}')