#CVE-2014-8609
>

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2014-8609/ "here"

##Description
The lazy_bdecode function in BitTorrent bootstrap-dht (aka Bootstrap) allows remote attackers to execute arbitrary code via a crafted packet, which triggers an out-of-bounds read, related to "Improper Indexing."	

##Additionnal Information
* Version Impacted : Android 4.0 to 4.4.4
* Role of the Component : Access Control

##CVSS Score & Vulnerability Types
* Cvss Score : 7.2
* CVSS Access : *Local*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Low*
* Authentication : *Not required*
* Gained Access : *Admin*
* CWE : [264] (http://cwe.mitre.org/data/definitions/264.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 1 
* **Total Commit**: 1
* **Total modified file**: 1 
* **Cloc**: 9


##Patch
####Description
SECURITY: Don't pass a usable Pending Intent to 3rd parties.

Unfortunately the Settings app has super powers. We shouldn't let
untrusted 3rd party authenticators re-purpose those powers to their own
nefarious ends.  This means that we shouldn't pass along PendingIntents
that can have addressing information (component, action, category)
filled in by third parties.


####Origin
* Language : Java
* Origin of the issue : Code -> Object not Rightly created
* Location : [platform_packages_apps_settings] (https://github.com/android/platform_packages_apps_settings)

####Patch
* **Kind of Patch** :  Changing call (changing argument)

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |   1    |    2  |
| Extended Cyclomatic Complexity  |     2   |   2    |
| Cyclomatic complexity           |     2  |  2     |

You can find here [the corresponding commit] (https://github.com/android/platform_packages_apps_settings/commit/f5d3e74ecc2b973941d8adbe40c6b23094b5abb7)  and the different file [in this folder] (patch/).