#CVE-2011-1823
>2 Corresponding Issue was found and 3 different commits (2 of them with the same modification).

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2011-1823/ "here"

##Description
The vold volume manager daemon on Android 3.0 and 2.x before 2.3.4 trusts messages that are received from a PF_NETLINK socket, which allows local users to execute arbitrary code and gain root privileges via a negative index that bypasses a maximum-only signed integer check in the DirectVolume::handlePartitionAdded method, which triggers memory corruption, as demonstrated by Gingerbreak.	

##Additionnal Information
* Version Impacted : Android 2.1 to 3.0
* Role of the Component : Network

##CVSS Score & Vulnerability Types
* Cvss Score : 7.2
* CVSS Access : *Local*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Low*
* Authentication : *Not Required*
* Gained Access : *Admin*
* CWE : [189] (http://cwe.mitre.org/data/definitions/189.html) 

##Corresponding Issue
https://android.googlesource.com/platform/system/vold/+/c51920c82463b240e2be0430849837d6fdc5352e
https://android.googlesource.com/platform/system/netd/+/79b579c92afc08ab12c0a5788d61f2dd2934836f
https://github.com/android/platform_system_core/commit/b620a0b1c7ae486e979826200e8e441605b0a5d6

###Complexity
* **Cycc total**: 11
* **Total Commit**: 3
* **Total modified file**: 3
* **Cloc**: 30


##Patch 1
####Description
vold: Enable the SO_PASSCRED socket option

Ensure that sender credentials are available when we
receive a netlink message.
####Origin
* Language : CPP
* Origin of the issue : Code -> Missing Incorrect Implemention of a feature 
* Location : [android /platform/system/vold] (https://android.googlesource.com/platform/system/vold/)

####Patch
* **Kind of Patch** : Add Condition
* **Cycc** : 3
* **Cloc** : 5

You can find here [the corresponding commit] (https://android.googlesource.com/platform/system/vold/+/c51920c82463b240e2be0430849837d6fdc5352e)  and the different file [in this folder] (patch1/).

##Patch 2 (link to patch 1)
####Description
netd: Enable the SO_PASSCRED socket option

Ensure that sender credentials are available when we
receive a netlink message.
####Origin
* Language : CPP
* Origin of the bug : Code -> Missing Incorrect Implemention of a feature 
* Location : [android /platform/system/netd] (https://android.googlesource.com/platform/system/netd/)

####Patch
* **Kind of Patch** : Add Condition
* **Cycc** : 3
* **Cloc** : 5

You can find here [the corresponding commit] (https://android.googlesource.com/platform/system/netd/+/79b579c92afc08ab12c0a5788d61f2dd2934836f/NetlinkManager.cpp)  and the different file [in this folder] (patch2/).

##Patch 3
####Description
Validate sender credentials on netlink msg receive
Verify that netlink messages are actually from the kernel,
and not from a userspace program.

####Origin
* Language : CPP
* Origin of the bug : Code -> Buffer Overflow / Input Not Verified
* Location : [android/platform_system_core] (https://github.com/android/platform_system_core)

####Patch
* **Kind of Patch** : Add Condition
* **Cycc** : 5
* **Cloc** : 20

You can find here [the corresponding commit] (https://github.com/android/platform_system_core/commit/b620a0b1c7ae486e979826200e8e441605b0a5d6)  and the different file [in this folder] (patch3/).
