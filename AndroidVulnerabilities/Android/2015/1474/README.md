#CVE-2015-1474
>

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2015-1474/ "here"

##Description
Multiple integer overflows in the GraphicBuffer::unflatten function in platform/frameworks/native/libs/ui/GraphicBuffer.cpp in Android through 5.0 allow attackers to gain privileges or cause a denial of service (memory corruption) via vectors that trigger a large number of (1) file descriptors or (2) integer values.	

##Additionnal Information
* Version Impacted : Android 5.0 
* Role of the Component : Library

##CVSS Score & Vulnerability Types
* Cvss Score : 10.0
* CVSS Access : *Network*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Low*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [189] (http://cwe.mitre.org/data/definitions/???.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 4
* **Total Commit**: 1
* **Total modified file**: 1
* **Cloc**: 13


##Patch
####Description
Fix for corruption when numFds or numInts is too large.

Bug: 18076253


####Origin
* Language : CPP
* Origin of the issue :  Code -> Buffer Overflow
* Location : [platform/frameworks/native] (https://android.googlesource.com/platform/frameworks/native/)

####Patch
* **Kind of Patch** : Add Condition (2)


You can find here [the corresponding commit] (https://android.googlesource.com/platform/frameworks/native/+/38803268570f90e97452cd9a30ac831661829091%5E%21/#F0)  and the different file [in this folder] (patch/).