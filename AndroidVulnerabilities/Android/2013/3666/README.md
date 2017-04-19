#CVE-2013-3666
>One issue found along with the exploit but no trace of the vulnerable code

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2013-3666/ "here"

##Description
The LG Hidden Menu component for Android on the LG Optimus G E973 allows physically proximate attackers to execute arbitrary commands by entering USB Debugging mode, using Android Debug Bridge (adb) to establish a USB connection, dialing 3845#*973#, modifying the WLAN Test Wi-Fi Ping Test/User Command tcpdump command string, and pressing the CANCEL button.	

##Additionnal Information
* Version Impacted : Android 4.1.2
* Role of the Component : Debug
* Vendor Specific : LG

##CVSS Score & Vulnerability Types
* Cvss Score : 7.2
* CVSS Access : *Local*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Low*
* Authentication : *Not required*
* Gained Access : *Admin*
* CWE : [264] (http://cwe.mitre.org/data/definitions/264.html) 

##Exploit
You can find here [the corresponding exploit] (http://packetstormsecurity.org/files/118539/Android-4.0.3-Browser-Crash.html)  and the different file [in this folder] (exploit/).
