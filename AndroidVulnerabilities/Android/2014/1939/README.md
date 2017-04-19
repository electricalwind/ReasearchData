#CVE-2014-1939
>One issue found with one commit

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2014-1939/ "here"

##Description
java/android/webkit/BrowserFrame.java in Android before 4.4 uses the addJavascriptInterface API in conjunction with creating an object of the SearchBoxImpl class, which allows attackers to execute arbitrary Java code by leveraging access to the searchBoxJavaBridge_ interface at certain Android API levels.	

##Additionnal Information
* Version Impacted : Android 4.0 to 4.3.1
* Role of the Component : Browsing

##CVSS Score & Vulnerability Types
* Cvss Score : 7.5
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *Partial*
* Availbility Impact : *Partial*
* Access Complexity : *Low*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [94] (http://cwe.mitre.org/data/definitions/94.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 5 (only removing part of code so Cycc of one per file)
* **Total Commit**: 1
* **Total modified file**: 5 (2 deleted)
* **Cloc**: 42 (without deleted files)


##Patch
####Description
Remove defunct searchbox implementation from webview.

The search box implementation has not been in use since ICS. This
removes dead code from webview.


####Origin
* Language : Java
* Origin of the issue : code -> Missing Incorrect Implemention of a feature  
* Location : [platform_frameworks_base] (https://github.com/android/platform_frameworks_base)

####Patch
* **Kind of Patch** : deleting files (2) deleting calls to those files (3)

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    1 & 70 & 2 |     1 & 67 & 1  |
| Extended Cyclomatic Complexity  |      5 & 111 & 2 |    5 & 108 & 1   |
| Cyclomatic complexity           |      5 & 114 & 3  |   5 & 111 & 1    |

You can find here [the corresponding commit] (https://android.googlesource.com/platform/frameworks/base/+/0e9292b94a3cb47374a8ac17f6287d98a426b1a8)  and the different file [in this folder] (patch/).