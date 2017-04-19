#CVE-2011-2357
>2 Corresponding Issue found in 2 commits.

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2011-2357/ "here"

##Description
Cross-application scripting vulnerability in the Browser URL loading functionality in Android 2.3.4 and 3.1 allows local applications to bypass the sandbox and execute arbitrary Javascript in arbitrary domains by (1) causing the MAX_TAB number of tabs to be opened, then loading a URI to the targeted domain into the current tab, or (2) making two startActivity function calls beginning with the targeted domain's URI followed by the malicious Javascript while the UI focus is still associated with the targeted domain.	

##Additionnal Information
* Version Impacted : Android 2.3.4 & 3.1
* Role of The Component : Browsing

##CVSS Score & Vulnerability Types
* Cvss Score : 4.3
* CVSS Access : *Network*
* Confidentiality Impact : *None*
* Integrity Impact : *Medium*
* Availbility Impact : *None*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [20] (http://cwe.mitre.org/data/definitions/20.html) 

##Corresponding Issues
###Complexity
* **Cycc total**: 8
* **Total Commit**: 2
* **Total modified file**: 1
* **Cloc**: 37


##Patch 1
####Description
DO NOT MERGE Security fix
 Bug: 4742007
####Origin
* Language : JAVA
* Origin of the Issue : Code -> Missing Incorrect Implementation of a feature 
* Location : [android/platform_packages_apps_browser] (https://github.com/android/platform_packages_apps_browser)

####Patch
* **Kind of Patch** : Complete Rewrite of Function
* **Cycc** : 5
* **Cloc** : 31

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    1    |     1   |
| Extended Cyclomatic Complexity  |      1    |    1    |
| Cyclomatic complexity           |      1    |   1      |

You can find here [the corresponding commit] (https://github.com/android/platform_packages_apps_browser/commit/afa4ab1e4c1d645e34bd408ce04cadfd2e5dae1e#diff-c6e2c334d624d5e475b44dad58ff7939)  and the different file [in this folder] (patch1/).

##Patch 2
####Description
DO NOT MERGE Prevent loading javascript: uris in existing tabs
 Bug: 4770356
####Origin
* Language : JAVA
* Origin of the Issue : Code -> Input Not Verified
* Location : [android/platform_packages_apps_browser] (https://github.com/android/platform_packages_apps_browser)

####Patch
* **Kind of Patch** : Add Condition
* **Cycc** : 3
* **Cloc** : 6

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |   11 & 10    |     12 & 10   |
| Extended Cyclomatic Complexity  |    32 & 10    |    34 & 11    |
| Cyclomatic complexity           |     25 &  10    |   26 & 10     |

You can find here [the corresponding commit] (https://github.com/android/platform_packages_apps_browser/commit/096bae248453abe83cbb2e5a2c744bd62cdb620b)  and the different file [in this folder] (patch2/).
