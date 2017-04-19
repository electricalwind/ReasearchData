#CVE-2010-4804
>1 Corresponding Issue in two distinct commit for a totl of 4 files to  patchs 

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2010-4804/ "here"

##Description
The Android browser in Android before 2.3.4 allows remote attackers to obtain SD card contents via crafted content:// URIs, related to (1) BrowserActivity.java and (2) BrowserSettings.java in com/android/browser/.	
##Additionnal Information
* Version Impacted : Android 1.5 to 2.3.3
* Role of the Component : Browsing

##CVSS Score & Vulnerability Types
* Cvss Score : 4.3
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *None*
* Availbility Impact : *None*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [200] (http://cwe.mitre.org/data/definitions/200.html) 

##Corresponding Bug
###Complexity
* **Cycc total**: 7
* **Total Commit**: 2
* **Total modified file**: 4
* **Cloc**: 19


###Patch 1 & 2
####Description
"Remove content:// protocol handler in web browser"

####Origin
* Language : JAVA
* Origin of the issue  : Code -> Semantic -> Missing Incorrect Implemention of a feature
* Location : [android/platform_packages_apps_browser] (https://android.googlesource.com/platform/packages/apps/Browser.git)

####Patch 1
* **Kind of Patch** : Removing Code
* **Cycc** : 2
* **Cloc** : 8

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    2    |    2   |
| Extended Cyclomatic Complexity  |     17   |   14    |
| Cyclomatic complexity           |     14   |  12     |

####Patch 2
* **Kind of Patch** : Add define
* **Cycc** : 1
* **Cloc** : 1

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    0    |    1   |
| Extended Cyclomatic Complexity  |     0   |   1    |
| Cyclomatic complexity           |     0   |  1     |

You can find here [the corresponding commit] (https://github.com/android/platform_packages_apps_browser/commit/604a598e1e01bda781600a45e0a971898a582666)  and the different file [here] (patch1/) and [here] (patch2/).


###Patch 3 & 4
####Description
Remove content:// protocol handler in web browser"
to Gingerbread

####Origin
* Language : JAVA
* Origin of the issue : Code -> Semantic -> Missing Incorrect Implemention of a feature
* Location : [android/platform_frameworks_base] (https://github.com/android/platform_frameworks_base)

#####Patch 3
  * **Kind of Patch** : Modify condition
  * **Cycc** : 2
  * **Cloc** : 3
  
  |  Complexity | Before | After |
  |---------------------------------|--------|-------|
  | Essential Cyclomatic Complexity |    7    |    7   |
  | Extended Cyclomatic Complexity  |     11   |   12    |
  | Cyclomatic complexity           |     11   |  11     |
  
#####Patch 4
  * **Kind of Patch** : Add method
  * **Cycc** : 2
  * **Cloc** : 7
  
  |  Complexity | Before | After |
  |---------------------------------|--------|-------|
  | Essential Cyclomatic Complexity |    1    |    1   |
  | Extended Cyclomatic Complexity  |     2   |   2    |
  | Cyclomatic complexity           |     1   |  1     |
  
 You can find [the corresponding commit](https://github.com/android/platform_frameworks_base/commit/7b7225c8fdbead25235c74811b30ff4ee690dc58) and the different file [here] (patch3/) and [here] (patch4/).
