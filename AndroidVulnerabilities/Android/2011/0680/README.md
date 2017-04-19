#CVE-2011-0680
>2 Corresponding Issue were found in 2 different commit .

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2011-0680/ "here"

##Description
data/WorkingMessage.java in the Mms application in Android before 2.2.2 and 2.3.x before 2.3.2 does not properly manage the draft cache, which allows remote attackers to read SMS messages intended for other recipients in opportunistic circumstances via a standard text messaging service.	

##Additionnal Information
* Version Impacted : Android 1.5 to 2.3
* Role of the Component : Messaging

##CVSS Score & Vulnerability Types
* Cvss Score : 5.0
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *None*
* Availbility Impact : *None*
* Access Complexity : *Low*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : Not Defined

##Corresponding Issues
###Complexity
* **Cycc total**: 6
* **Total Commit**: 2
* **Total modified file**: 2
* **Cloc**: 14


###Issue 1 
####Description
Selecting sms notification often goes to conversation list instead
of the individual conversation. Bug 3322081

Merged from gingerbread

####Origin
* Language : JAVA
* Origin of the issue  : Code -> Semantic -> Missing Incorrect Implementation of a feature
* Location : [android/platform_packages_apps_mms] (https://android.googlesource.com/platform/packages/apps/Mms.git)

####Patch
* **Kind of Patch** : Add Condition
* **Cycc** : 1
* **Cloc** : 2

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    1    |    1   |
| Extended Cyclomatic Complexity  |     3   |   4    |
| Cyclomatic complexity           |     3   |  4     |


You can find here [the corresponding commit] (https://github.com/android/platform_packages_apps_mms/commit/4d26623ce82230e8e7009adb921c5edea370a9e0)  and the different file [here] (patch1/).

###Issue 2 
####Description
Sms sent to wrong recipient
Remove the empty conversation from the conversation cache.
Bug 3057952
 

####Origin
* Language : JAVA
* Origin of the issue  : Code -> Semantic -> Missing Incorrect Implementation of a feature
* Location : [android/platform_packages_apps_mms] (https://android.googlesource.com/platform/packages/apps/Mms.git)

####Patch
* **Kind of Patch** : Add Condition
* **Cycc** : 5
* **Cloc** : 12

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    2 & 1 & 0   |    2 & 1 & 1   |
| Extended Cyclomatic Complexity  |     4 & 2 & 0   |   4 & 2 & 3  |
| Cyclomatic complexity           |     4 & 2 & 0  |  4 & 2 & 3    |


You can find here [the corresponding commit] (https://github.com/android/platform_packages_apps_mms/commit/18d6b7e9d2e538fb3c0264332b96c02abf367267)  and the different file [here] (patch2/).
