#CVE-2014-7911
>

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2014-7911/ "here"

##Description
Multiple SQL injection vulnerabilities in the queryLastApp method in packages/WAPPushManager/src/com/android/smspush/WapPushManager.java in the WAPPushManager module in Android before 5.0.0 allow remote attackers to execute arbitrary SQL commands, and consequently launch an activity or service, via the (1) wapAppId or (2) contentType field of a PDU for a malformed WAPPush message, aka Bug 17969135.

##Additionnal Information
* Version Impacted : Android 1.0 to 4.4.4
* Role of the Component : Library

##CVSS Score & Vulnerability Types
* Cvss Score : 7.2
* CVSS Access : *Local*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Low*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [264] (http://cwe.mitre.org/data/definitions/264.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 7 
* **Total Commit**: 1
* **Total modified file**: 2
* **Cloc**: 42
* Metric Test: 8.8

##Patch
####Description
Add additional checks in ObjectInputStream

Thanks to Jann Horn for reporting a bug in ObjectInputStream
and sending the initial patch.

Add some checks that the class of an object
being deserialized still conforms to the requirements
for serialization.

Add some checks that the class being deserialized matches
the type information (enum, serializable, externalizable)
held in the stream.

Delayed static initialization of classes until the
type of the class has been validated against the stream
content in some cases.

Added more tests.


####Origin
* Language : Java
* Origin of the issue :  Code -> Serialization Issue
* Location : [platform/libcore ] (https://android.googlesource.com/platform/libcore/)

####Patch
* **Kind of Patch** : Add method / (condition and exception raising)
 
 |  Complexity | Before | After |
 |---------------------------------|--------|-------|
 | Essential Cyclomatic Complexity |    (0 & 0) & (5 & 6) |     (2 & 5) & (5 & 6)  |
 | Extended Cyclomatic Complexity  |      (0 & 0) & (5 & 13) |    (2 & 5) & (5 & 13)   |
 | Cyclomatic complexity           |      (0 & 0) & (5 & 14) |   (2 & 5) & (5 & 14)    |

You can find here [the corresponding commit] (https://android.googlesource.com/platform/libcore/+/738c833d38d41f8f76eb7e77ab39add82b1ae1e2)  and the different file [in this folder] (patch/).