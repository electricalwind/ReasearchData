#CVE-2014-8610
>

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2014-8610/ "here"

##Description
AndroidManifest.xml in Android before 5.0.0 does not require the SEND_SMS permission for the SmsReceiver receiver, which allows attackers to send stored SMS messages, and consequently transmit arbitrary new draft SMS messages or trigger additional per-message charges from a network operator for old messages, via a crafted application that broadcasts an intent with the com.android.mms.transaction.MESSAGE_SENT action, aka Bug 17671795.	

##Additionnal Information
* Version Impacted : Android 1.0 to 4.4.4
* Role of the Component : Access Control

##CVSS Score & Vulnerability Types
* Cvss Score : 3.3
* CVSS Access : *Local*
* Confidentiality Impact : *Partial*
* Integrity Impact : *Partial*
* Availbility Impact : *None*
* Access Complexity : *Medium*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [264] (http://cwe.mitre.org/data/definitions/264.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 1
* **Total Commit**: 1
* **Total modified file**: 1
* **Cloc**: 3


##Patch
####Description
Externally Reported Low Severity Security Vulnerability: SMS Resend Vulnerability in Android

Bug 17671795

Require SEND_SMS permission so apps without it won't be able to trick
the messaging app into sending messages.


####Origin
* Language : XML
* Origin of the issue :  Code -> Unauthorized access
* Location : [platform/packages/apps/Mms] (https://android.googlesource.com/platform/packages/apps/Mms/)

####Patch
* **Kind of Patch** : Add Authorization permission

You can find here [the corresponding commit] (https://android.googlesource.com/platform/packages/apps/Mms/+/008d6202fca4002a7dfe333f22377faa73585c67)  and the different file [in this folder] (patch/).