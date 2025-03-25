# FileByteDisplayer
A small C program to display byte information of any file.

## Usage
1. Compile the code
2. In terminal write the following command:
```
fileBitDisplayer.exe <filePath>
```
### Explanation
<filePath> – a path to the file the bytes of which are to be displayed

### Optional flags
-s <startLineNumber> - specify the first line to be displayed (all the previous bytes will be skipped).
-e <endLineNumber> - specify the last line number to be displayed (all the following bytes will be skipped).
-c <lineCountNumber> - specify the maximum number of lines to be displayed.

NOTE: all the bytes are displayed in lines each consisting of 16 bytes (although the last line may have fewer bytes).
