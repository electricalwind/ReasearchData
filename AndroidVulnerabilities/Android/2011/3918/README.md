#CVE-2011-3918
>1 Corresponding Issue was found and 1 patch found.

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2011-3918/ "here"

##Description
The Zygote process in Android 4.0.3 and earlier accepts fork requests from processes with arbitrary UIDs, which allows remote attackers to cause a denial of service (reboot loop) via a crafted application.

##Additionnal Information
* Version Impacted : Android 1.0 to 4.0.3
* Component : Network

##CVSS Score & Vulnerability Types
* Cvss Score : 7.8
* CVSS Access : *Network*
* Confidentiality Impact : *None*
* Integrity Impact : *None*
* Availbility Impact : *Complete*
* Access Complexity : *Low*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [399] (http://cwe.mitre.org/data/definitions/399.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 1
* **Total Commit**: 1
* **Total modified file**: 1
* **Cloc**: 1


###Description
Restrict zygote to system user.

CVE-2011-3918: Address denial of service attack against Android's
zygote process. This change enforces that only UID=system can
directly connect to zygote to spawn processes.
  
###Origin
* Language : RC
* Origin of the Issue: Design Error -> Unauthorized Access
* Location : [android-source-browsing] (https://code.google.com/p/android-source-browsing/)
[platform-system-core](https://android.googlesource.com/platform/system/core/)

###Patch
* **Kind of Patch** : Modify Authorization
* **Cycc** : 1
* **Cloc** : 1


You can find the corresponding commit [there] and the different file [here] (patch1/).
[there]: https://code.google.com/p/android-source-browsing/source/detail?repo=platform--system--core&r=e7fd911fd42b "here"

