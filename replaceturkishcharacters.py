#!/bin/python

# -*- coding: utf-8 -*-


text = open("text.txt",'r').read()

print "Original text: " + text
print

text = text.lower()
print "Lower-cased text: " + text
print

mapping = [ ('ı', 'i'), ('ş', 's'), ('ç', 'c'), ('ğ', 'g'), ('ö', 'o'), ('ü', 'u'), ('İ', 'i') ]

for k, v in mapping:
    text = text.replace(k, v)

print "After character replacement: " + text
print

open("filtered_text.txt",'w').write(text)
print "text was written into a file!"
