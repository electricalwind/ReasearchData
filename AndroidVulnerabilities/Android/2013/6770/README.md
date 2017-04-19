#CVE-2013-6770
>No patch found

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2013-6770/ "here"

##Description
The CyanogenMod/ClockWorkMod/Koush Superuser package 1.0.2.1 for Android 4.3 and 4.4 does not properly restrict the set of users who can execute /system/xbin/su with the --daemon option, which allows attackers to gain privileges by leveraging ADB shell access and a certain Linux UID, and then creating a Trojan horse script.

##Additionnal Information
* Version Impacted : Android 4.3 to 4.4
* Role of the Component : Access Control
* Software Specific : Koush Superuser

##CVSS Score & Vulnerability Types
* Cvss Score : 7.6
* CVSS Access : *Network*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *High*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [264] (http://cwe.mitre.org/data/definitions/264.html) 

