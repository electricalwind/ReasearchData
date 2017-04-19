#CVE-2011-2344
>1 Corresponding Issue was found with one commit  and 3 patched file 

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2011-2344/ "here"

##Description
Android Picasa in Android 3.0 and 2.x through 2.3.4 uses a cleartext HTTP session when transmitting the authToken obtained from ClientLogin, which allows remote attackers to gain privileges and access private pictures and web albums by sniffing the token from connections with picasaweb.google.com.	

##Additionnal Information
* Version Impacted : Android 2.1 to 3.0
* Role of the Component : Browsing

##CVSS Score & Vulnerability Types
* Cvss Score : 10
* CVSS Access : *Network*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Low*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [310] (http://cwe.mitre.org/data/definitions/310.html) 

##Corresponding Bug
###Complexity
* **Cycc total**: 5
* **Total Commit**: 1
* **Total modified file**: 3
* **Cloc**: 18

###Description
Fix 4442284 Android Picasa sync over HTTP - data and credentials sent in clear text.

* Origin of the bug : Design -> Insecure Protocol

Location : [platform/packages/apps/Gallery3D] (https://android.googlesource.com/platform/packages/apps/Gallery3D/)
You can find here [the corresponding commit] (https://android.googlesource.com/platform/packages/apps/Gallery3D/+/7a763db1c15bb6436be85a3f23382e4171970b6e)  
###Patch 1 
####Origin
* Language : JAVA

####Patch
* **Kind of Patch** : Add Line
* **Cycc** : 1
* **Cloc** : 2

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    N.C    |     N.C    |
| Extended Cyclomatic Complexity  |      N.C    |    N.C     |
| Cyclomatic complexity           |      N.C    |   N.C      |

Corresponding files [in this folder] (patch1/).

###Patch 2
####Origin
* Language : JAVA

#####Patch
  * **Kind of Patch** : Modify methods
  * **Cycc** : 3
  * **Cloc** : 14
  
  |  Complexity | Before | After |
  |---------------------------------|--------|-------|
  | Essential Cyclomatic Complexity |    6    |    6    |
  | Extended Cyclomatic Complexity  |      9    |   9     |
  | Cyclomatic complexity           |      8    |   8      |
  
Corresponding files [in this folder] (patch2/).

###Patch 3
####Origin
* Language : JAVA

#####Patch
  * **Kind of Patch** : Modify Call
  * **Cycc** : 1
  * **Cloc** : 2
  
  |  Complexity | Before | After |
  |---------------------------------|--------|-------|
  | Essential Cyclomatic Complexity |    N.C    |     N.C    |
  | Extended Cyclomatic Complexity  |      N.C    |    N.C     |
  | Cyclomatic complexity           |      N.C    |   N.C      |
  
Corresponding files [in this folder] (patch3/).
