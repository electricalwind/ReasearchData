#CVE-2010-4832
>1 issue found in one commit and 4 files to patch

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2010-4832/ "here"

##Description
The Android browser in Android before 2.3.4 allows remote attackers to obtain SD card contents via crafted content:// URIs, related to (1) BrowserActivity.java and (2) BrowserSettings.java in com/android/browser/.	
##Additionnal Information
* Version Impacted : Android 1.0 to 2.1
* Role of the Component : Cryptography

##CVSS Score & Vulnerability Types
* Cvss Score : 4.3
* CVSS Access : *Network*
* Confidentiality Impact : *None*
* Integrity Impact : *Partial*
* Availbility Impact : *None*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [310] (http://cwe.mitre.org/data/definitions/310.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 7
* **Total Commit**: 1
* **Total modified file**: 4
* **Cloc**: 9


###Patch 
####Description
Two more cases of "View certificate" problems like b/2511635

One problem is that if there are multiple resources downloaded for a
page. In that case the mCertificate shown ends up being from the last
loaded resource instead of the main resource of the page. The solution
is to only set the certificate if the LoadListener is the
mIsMainResourceLoader as well as the mIsMainPageLoader.

A larger problem was the fact that the EventHandler.certificate
interface method (in this case the LoadListener.certificate
implementation) once per https connection instead of once per request
as was documented. That meant if an https connection was reused (which
happens frequently on login pages such as
https://www.google.com/accounts which use the POST -> redirect -> GET
idiom to avoid POST data page refresh warnings) then later pages never
were associated with an SslCertificate.

The solution was to change EventHandler.certificate to be called once
per request, specifcally before the request. This means we no longer
call the certificate method in the handleSslErrorRequest case, which
is okay because it includes the SslCertificate within the SslError and
that is what the BrowserActivity expects.

Change-Id: Icbd9bd98c89db82762d1d06de85e1cde2470300d

####Origin
* Language : JAVA
* Origin of the issue : Design -> Flow
* Location : [android/platform_frameworks_base] (https://github.com/android/platform_frameworks_base)


####Patch 1
* **Kind of Patch** : add Verification
* **Cycc** : 1
* **Cloc** : 1

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    12    |    12   |
| Extended Cyclomatic Complexity  |     26   |   26    |
| Cyclomatic complexity           |     23   |  23     |

####Patch 2

* **Kind of Patch** : add Verification
* **Cycc** : 1
* **Cloc** : 2

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    6    |    6   |
| Extended Cyclomatic Complexity  |     22   |   22    |
| Cyclomatic complexity           |     21   |  21     |

####Patch 3

* **Kind of Patch** : add Verification
* **Cycc** : 3
* **Cloc** : 4

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |   1 & 1    |    1 & 1  |
| Extended Cyclomatic Complexity  |    2 & 1   |   3 & 2   |
| Cyclomatic complexity           |    2 & 1    |  2 & 2    |


####Patch 4

* **Kind of Patch** : add Verification
* **Cycc** : 2
* **Cloc** : 2

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    1    |    1   |
| Extended Cyclomatic Complexity  |     1   |   2    |
| Cyclomatic complexity           |     1   |  2     |



You can find here [the corresponding commit] (https://github.com/android/platform_frameworks_base/commit/dba8cb76371960457e91b31fa396478f809a5a34 )  and the different file [here for patch1] (patch1/) 
,[here for patch 2] (patch2/),[here for patch 3] (patch3/) and [here for patch 4] (patch4/).


