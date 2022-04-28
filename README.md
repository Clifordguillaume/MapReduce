# MapReduce
by Elizabeth Dwulit and Cliford Guillaume

CSE 687 Object Oriented Design
Project MapReduce
Phase #1

Github: https://github.com/Clifordguillaume/MapReduce

This MapReduce program reads in data from a given input file directory,
counts the words in each file and their frequencies, sorts the words in
alphabetical order, then reduces the data by summing up the frequencies
and writing the results to an output file.

# How to use the program:
- The MapReduce.exe is located in MapReduce/x64/Release directory. If Release does not run, try using the exe in MapReduce/x64/Debug directory instead.
- Run MapReduce.exe [input file directory path] [output file directory path] [temp file drectory path]
- (The above should not include the brackets)
- The final result will be written to a text file in the output file directory as FinalReducedData-x.txt

# Steps on how it works:
- Reads all the text file from a given input diretory.
- Parse each file to locate single words using the map class and write the data to a specified temp output directory.
- Call the reduce function to locate the key and the fequency of each single word found.
- Export the reduced data to a new file in the output directory and create an empty SUCCESS.txt file.

# Basic Program functionality:
- Read a given text file.
- Extract words from the file.
- Measure the frequency of each word.
- Export the data to a new text file.

# Possible issue fixes if running in Visual Studio:
- If glog has issues linking, install the glog package with vcpkg https://vcpkg.io/en/getting-started.html
	1. git clone https://github.com/Microsoft/vcpkg.git
	2. run the bootstrap-vcpkg.bat file
	3. in the vcpkg directory run the following ".\vcpkg install glog:x64-windows"
	4. in the same vcpkg directory run the following ".\vcpkg integrate install"
	5. You may have to remove and re-add the glog package to the MapReduce project
- If boost libraries not found, download boost and add it to the MapReduce project
	1. Download and unzip boost from here: https://www.boost.org/users/download/
	2. Add boost to the MapReduce project
		a. Right click the MapReduce project
		b. Properties -> C++ -> General -> Additional Include Directories
		c. Add the path to the downloaded boost folder (ex: C:\Users\example\Downloads\boost_1_78_0_rc1\boost_1_78_0)
