#CVE-2013-4777
>One issue and the vulnerable code but no 

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2013-4777/ "here"

##Description
A certain configuration of Android 2.3.7 on the Motorola Defy XT phone for Republic Wireless uses init to create a /dev/socket/init_runit socket that listens for shell commands, which allows local users to gain privileges by interacting with a LocalSocket object.	

##Additionnal Information
* Version Impacted : Android 
* Role of the Component : Networking
* Vendor Specific : Motorola

##CVSS Score & Vulnerability Types
* Cvss Score : 6.9
* CVSS Access : *Local*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Medium*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [16] (http://cwe.mitre.org/data/definitions/16.html) 

##Corresponding Issue
####Description
Debug/test feature in init allows any user to execute shell commands as the root user on some Motorola and Sharp devices.

Lets see if we can bump my embarrassing presentation further down the page...

This vulnerability is being published now as the responsible parties have informed me that it will not be fixed due to no planned updates for the device. Very few devices are affected, seems to be limited to one small carrier (Republic Wireless) in the US.

 At boot time init creates a socket at /dev/socket/init_runit, and accepts shell commands. When a command is sent, init executes the command as the root user.

####Origin
* Language : Java
* Origin of the issue : Design -> Unauthorized Access

####Patch
No patch planned

You can find here [the corresponding explanation] (https://plus.google.com/+JustinCaseAndroid/posts/5ofgPNrSu3J)  and the vulnerable file [in this folder] (vulnerablecode/).