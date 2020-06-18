---Compiling the tool---

To compile the tool you need to include all of these files:

vignere_cracker.cpp         contains the main function
rauheitsgrad.cpp            contains functions to determine the rauheitsgrad
key_lengths.cpp             contains functions to determine the possible lengths of the key
calc_key.cpp                contains functions to determine the key to a given Keylength
basic_functions.cpp         contains basic functions used by all of the above

The corresponding header files should also be available.

---Using the tool---

The commandline tool takes 2 arguments in the following order:

vignere_cracker <cryptotextfile> [maximum Keylength]

cryptotextfile:     the name of the file you want to crack with the vignere vignere_cracker
                    the file needs to be in the same directory as the commandline tool
                    this is a mandatory argument

maximum keylength:  optional value to set the longest key to be tested
                    default value: 100

The tool outputs the plaintext and the key that was used to decrypt the cryptotext.

---The output was nonsense!---
There are a few possible causes for a nonsensical output:
1.  you entered a maximum keylength, that is too low to determine the actual key
2.  the given cryptotext was not vignere encrypted
