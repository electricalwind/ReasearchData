#CVE-2013-7372
>

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2013-7372/ "here"

##Description
The engineNextBytes function in classlib/modules/security/src/main/java/common/org/apache/harmony/security/provider/crypto/SHA1PRNG_SecureRandomImpl.java in the SecureRandom implementation in Apache Harmony through 6.0M3, as used in the Java Cryptography Architecture (JCA) in Android before 4.4 and other products, when no seed is provided by the user, uses an incorrect offset value, which makes it easier for attackers to defeat cryptographic protection mechanisms by leveraging the resulting PRNG predictability, as exploited in the wild against Bitcoin wallet applications in August 2013.	

##Additionnal Information
* Version Impacted : Android 4.0 to 4.3.1
* Role of the Component : Cryptography
* Software Specific : Apache Harmony

##CVSS Score & Vulnerability Types
* Cvss Score : 5.0
* CVSS Access : *Network*
* Confidentiality Impact : *None*
* Integrity Impact : *Partial*
* Availbility Impact : *None*
* Access Complexity : *Low*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [310] (http://cwe.mitre.org/data/definitions/310.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 2
* **Total Commit**: 1 
* **Total modified file**: 1
* **Cloc**: 1


##Patch 1
####Description
Make sure seed values use full range
Bug: 6642616

####Origin
* Language : Java
* Origin of the issue : Code -> Wrong Initialization of Data 
* Location : [platform/libcore] (https://android.googlesource.com/platform/libcore/)

####Patch
* **Kind of Patch** : Add condition (ternaire)

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    6    |     6   |
| Extended Cyclomatic Complexity  |      16    |    16    |
| Cyclomatic complexity           |      16    |   16      |

You can find here [the corresponding commit] (https://android.googlesource.com/platform/libcore/+/ab6d7714b47c04cc4bd812b32e6a6370181a06e4%5E%21/#F0)  and the different file [in this folder] (patch/).