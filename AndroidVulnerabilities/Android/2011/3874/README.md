#CVE-2011-3874
>No Corresponding Issue found

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2011-3874/ "here"

##Description
Stack-based buffer overflow in libsysutils in Android 2.2.x through 2.2.2 and 2.3.x through 2.3.6 allows user-assisted remote attackers to execute arbitrary code via an application that calls the FrameworkListener::dispatchCommand method with the wrong number of arguments, as demonstrated by zergRush to trigger a use-after-free error.	

##Additionnal Information
* Version Impacted : Android 2.2 to 2.3.6
* Role of the Component : Library
* Language : CPP
* Origin of the Issue : Code -> Buffer Overflow

##CVSS Score & Vulnerability Types
* Cvss Score : 9.3
* CVSS Access : *Network*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [119] (http://cwe.mitre.org/data/definitions/119.html) 
