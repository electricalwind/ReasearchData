#CVE-2011-1149
>1 Corresponding Issue was found and with 2 patched file.

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2011-1149/ "here"

##Description
Android before 2.3 does not properly restrict access to the system property space, which allows local applications to bypass the application sandbox and gain privileges, as demonstrated by psneuter and KillingInTheNameOf, related to the use of Android shared memory (ashmem) and ASHMEM_SET_PROT_MASK.	

##Additionnal Information
* Version Impacted : Android 1.5 to 2.2.2
* Role of the Component : Access Control

##CVSS Score & Vulnerability Types
* Cvss Score : 7.2
* CVSS Access : *Local*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Low*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [264] (http://cwe.mitre.org/data/definitions/264.html) 

##Corresponding Issue
###Description
init: use tmpfs/ftruncate for properties backing store instead of ashmem
This removes the need for ashmem for early bringup and avoids an issue
with permissions enforcement.
You can find here [the corresponding commit] (https://github.com/android/platform_system_core/commit/25b15be9120bcdaa0aba622c67ad2c835d9e91ca) 

###Complexity
* **Cycc total**: 3
* **Total Commit**: 1
* **Total modified file**: 2
* **Cloc**: 3


###Patch 1:
####Origin
* Language : C
* Origin of the Issue  : Code -> Semantic -> Unprotected Use of function
* Location : [android/platform_system_core] (https://github.com/android/platform_system_core)

####Patch
* **Kind of Patch** : Removing Use of a Library
* **Cycc** : 4
* **Cloc** : 13

Corresponding files [in this folder] (patch1/).

###Patch 2
####Origin
* Language : C
* Origin of the Issue : Code -> Semantic -> Missing or Incorrect implementation of a feature
* Location : [android/kernel_common] (https://github.com/android/kernel_common)

#####Patch
  * **Kind of Patch** : Add Define
  * **Cycc** : 2
  * **Cloc** : 9
  
Corresponding files [in this folder] (patch2/).