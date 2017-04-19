#CVE-2013-4787
>One issue was found here with 

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2013-4787/ "here"

##Description
Android 1.6 Donut through 4.2 Jelly Bean does not properly check cryptographic signatures for applications, which allows attackers to execute arbitrary code via an application package file (APK) that is modified in a way that does not violate the cryptographic signature, probably involving multiple entries in a Zip file with the same name in which one entry is validated but the other entry is installed, aka Android security bug 8219321 and the "Master Key" vulnerability.	

##Additionnal Information
* Version Impacted : Android 1.6 to 4.2
* Role of the Component : Cryptography

##CVSS Score & Vulnerability Types
* Cvss Score : 9.3
* CVSS Access : *Network*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Medium*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [310] (http://cwe.mitre.org/data/definitions/310.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 2
* **Total Commit**: 1
* **Total modified file**: 1
* **Cloc**: 4


##Patch 
####Description
Remove support for duplicate file entries


####Origin
* Language : Java
* Origin of the issue :  Design -> Flow
* Location : [android_libcore] (https://github.com/CyanogenMod/android_libcore)

####Patch
* **Kind of Patch** : Add Condition / exception

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    6    |     8   |
| Extended Cyclomatic Complexity  |      8    |    9    |
| Cyclomatic complexity           |      8    |   9      |

You can find here [the corresponding commit] (http://review.cyanogenmod.org/#/c/45251/1/luni/src/main/java/java/util/zip/ZipFile.java)  and the different file [in this folder] (patch/).