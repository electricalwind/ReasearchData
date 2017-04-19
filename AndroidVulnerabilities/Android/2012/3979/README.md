#CVE-2012-3979
>One corresponding issue found impacting 5 different file

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2012-3979/ "here"

##Description
Mozilla Firefox before 15.0 on Android does not properly implement unspecified callers of the __android_log_print function, which allows remote attackers to execute arbitrary code via a crafted web page that calls the JavaScript dump function.	

##Additionnal Information
* Version Impacted : Android -> Firefox Mobile 0.1 to 10.0.4
* Role of the Component : Browsing
* Software Specific : Mozilla Firefox Mobile

##CVSS Score & Vulnerability Types
* Cvss Score : 6.8
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *Partial*
* Availbility Impact : *Partial*
* Access Complexity : *Medium*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [20] (http://cwe.mitre.org/data/definitions/20.html) 

##Corresponding Issue
#Description
(CVE-2012-3979) Audit for incorrect uses of __android_log_print
The 5 file have similar modification 

###Complexity
* **Cycc total**: 5
* **Total Commit**: 1
* **Total modified file**: 5
* **Cloc**: 10


####Origin
* Language : CPP 
* Origin of the issue : Unprotected Use of Function 
* Location : [Core] (https://wiki.mozilla.org/Modules/All#Core)

####Patch (Same for the 5 file)
* **Kind of Patch** : Modify calls to function 
* **Cycc** : 1
* **Cloc** : 1

You can find here [the corresponding commit] (https://bugzilla.mozilla.org/attachment.cgi?id=637506&action=diff)  and the different file [in this folder] (patch/).
