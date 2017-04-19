#CVE-2009-2656
>one Corresponding Issue and one Commit was found for this vulnerability

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2009-2656/ "here"

##Description
Android 1.5 CRBxx allows local users to bypass the (1) Manifest.permission.CAMERA (aka android.permission.CAMERA) and (2) Manifest.permission.AUDIO_RECORD (aka android.permission.RECORD_AUDIO) configuration settings by installing and executing an application that does not make a permission request before using the camera or microphone.		

##Additionnal Information
* Version Impacted : Android 1.0 1.1 1.5
* Role of the Component : Messaging

##CVSS Score & Vulnerability Types
* Cvss Score : 5.0
* CVSS Access : *Network*
* Confidentiality Impact : *None*
* Integrity Impact : *None*
* Availbility Impact : *Partial*
* Access Complexity : *Low*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : Not Defined

##Corresponding Issue
###Complexity
* **Cycc total**: 4
* **Total Commit**: 1
* **Total modified file**: 2
* **Cloc**: 14


###Description
Manual merge of https://android-git.corp.google.com/g/Gerrit#change,5804 from donut:
  Ensure that we never trigger ArrayIndexOutOfBoundsException by checking that
  the index is always < the array's length. Also ensures that the object's
  state is consistent. Should resolve a denial-of-service bug when handling
  malformed WAP pushes.
  Also add a try-catch around call to dispatchMessage(), in case there are other lurking bugs.  (This is also already in Donut.)

Automated import of CL 150264

Location : [android/platform_frameworks_base] (https://github.com/android/platform_frameworks_base)
You can find here [the corresponding commit] (https://github.com/android/platform_frameworks_base/commit/46e23fe762d2143d60589ab6d39c4b47c2c754d1)  
###Patch 1 
####Origin
* Language : Java
* Origin of the issue : Code -> Data -> Input Not Verified

####Patch
* **Kind of Patch** : Add Condition
* **Cycc** : 2
* **Cloc** : 8

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    1    |    1   |
| Extended Cyclomatic Complexity  |     2   |   3    |
| Cyclomatic complexity           |     2   |  2     |

Corresponding files [in this folder] (patch1/).

###Patch 2
####Origin
* Language : Java
* Origin of the issue: Code -> Semantic -> Unprotected Use of function

#####Patch
  * **Kind of Patch** : Add Authorization permission
  * **Cycc** : 2
  * **Cloc** : 6
  
  |  Complexity | Before | After |
  |---------------------------------|--------|-------|
  | Essential Cyclomatic Complexity |    10    |    10   |
  | Extended Cyclomatic Complexity  |     14   |   14    |
  | Cyclomatic complexity           |     14   |  14     |
Corresponding files [in this folder] (patch2/).

