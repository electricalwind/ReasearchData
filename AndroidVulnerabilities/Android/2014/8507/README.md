#CVE-2014-8507
>

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2014-8507/ "here"

##Description
Multiple SQL injection vulnerabilities in the queryLastApp method in packages/WAPPushManager/src/com/android/smspush/WapPushManager.java in the WAPPushManager module in Android before 5.0.0 allow remote attackers to execute arbitrary SQL commands, and consequently launch an activity or service, via the (1) wapAppId or (2) contentType field of a PDU for a malformed WAPPush message, aka Bug 17969135.	

##Additionnal Information
* Version Impacted : Android 1.0 to 4.4.4
* Role of the Component : Messaging

##CVSS Score & Vulnerability Types
* Cvss Score : 7.5
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *Partial*
* Availbility Impact : *Partial*
* Access Complexity : *Low*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [89] (http://cwe.mitre.org/data/definitions/89.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 6 
* **Total Commit**: 1
* **Total modified file**: 1
* **Cloc**: 25


##Patch 
####Description
Bug 17969135

Use query (instead of rawQuery) and pass in arguments instead of building
the query with a giant string. Add a unit test that fails with the old
code but passes with the new code.


####Origin
* Language : Java
* Origin of the issue :  Code -> Input not Verified
* Location : [platform_frameworks_base] (https://github.com/android/platform_frameworks_base)

####Patch
* **Kind of Patch** : Change call

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    1 & 3 |     1 & 3  |
| Extended Cyclomatic Complexity  |      3 & 3 |    3 & 5   |
| Cyclomatic complexity           |      3 & 3  |   3 & 5    |

You can find here [the corresponding commit] (https://android.googlesource.com/platform/frameworks/base/+/48ed835468c6235905459e6ef7df032baf3e4df6%5E%21/#F0)  and the different file [in this folder] (patch/).