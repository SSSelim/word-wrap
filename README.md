# Word-Wrap Algorithm
It finds the best way to divide given text in lines so that the total count of spaces at the end
of each line is as few as possible. Dynamic programming was used to the problem.

* M is maximum charachters that can be put on a line.
* Each space at the end of the line has a cubic cost.

## Text
Given text was in turkish, not to have wierd character problem. I wrote a basic
python script to replace turkish characters.

## Usage

```shell
# if you want to recreate filtered_text file
$ python replaceturkishcharacters.py  # it could take file name as parameter

$ c99 word-wrap.c -o word-wrap
# if c99 doesnt work 
$ gcc word-wrap.c -o word-wrap -std=c99

$ ./word-wrap   # text file and M could be taken as parameters
```



