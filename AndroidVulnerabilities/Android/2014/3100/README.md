#CVE-2014-3100
>

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2014-3100/ "here"

##Description
Stack-based buffer overflow in the encode_key function in /system/bin/keystore in the KeyStore service in Android 4.3 allows attackers to execute arbitrary code, and consequently obtain sensitive key information or bypass intended restrictions on cryptographic operations, via a long key name.	

##Additionnal Information
* Version Impacted : Android 4.3
* Role of the Component : Cryptography

##CVSS Score & Vulnerability Types
* Cvss Score : 5.1
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *Partial*
* Availbility Impact : *Partial*
* Access Complexity : *High*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [119] (http://cwe.mitre.org/data/definitions/119.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 2
* **Total Commit**: 1
* **Total modified file**: 1
* **Cloc**: 8


##Patch
####Description
The function getKeyForName no longer uses a C-style string to store the filename. In addition, it calls getKeyNameForUidWithDir instead of encode_key_for_uid to generate the encoded key name. The former properly calculates the length of the encoded key.


####Origin
* Language : CPP
* Origin of the issue : Code -> Buffer Overflow \ Input verification

####Patch
* **Kind of Patch** : Add function / proper allocation

You can find the exploit [here] (exploit/), the patch [in this folder] (patch/) and more information [here] (pdf/).