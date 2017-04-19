#CVE-2009-1754
>one Corresponding Issue was found there.

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2009-1754/ "here"

##Description
The PackageManagerService class in services/java/com/android/server/PackageManagerService.java in Android 1.5 through 1.5 CRB42 does not properly check developer certificates during processing of sharedUserId requests at an application's installation time, which allows remote user-assisted attackers to access application data by creating a package that specifies a shared user ID with an arbitrary application.	

##Additionnal Information
* Version Impacted : Android 1.5
* Role of the Component : Cryptography

##CVSS Score & Vulnerability Types
* Cvss Score : 4.3
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *None*
* Availbility Impact : *None*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [287] (http://cwe.mitre.org/data/definitions/287.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 1
* **Total Commit**:1
* **Total modified file**: 1
* **Cloc**: 1


###Description
AI 148824: Fix issue #1851541 (sharedUserId requests not being checked for matching signatures on .apk).

  To address issues where we could leave half-installed applications around if there was a failure during the install, we split getPackageLP() into two phases: the first would create the record, and only after doing all verification checks would we call insertPackageSettingLP() to do the remaining part of the original implementation and actually insert the record into the data structures.
  Unfortunately it was only in insertPackageSettingLP() that we would set the sharedUser field of the PackageSetting structure, so when before that we went to verify certificates, we didn't think it had requested a shared user ID, and let it through without checking.
  This fix simply sets the sharedUser field when the PackageSetting structure is first created, so we will actually check against its certs.  We still also set this again in insertPackageSettingLP(), but there is no harm in this because the only time we call this function is in that big install func, which just passes in the same shared user that it had when first getting the package.
  BUG=1851541
  
###Origin
* Language : Java
* Origin of the Issue: Design Error -> Flow
* Location : [android/platform_frameworks_base] (https://github.com/android/platform_frameworks_base)

###Patch
* **Kind of Patch** : Set A value
* **Cycc** : 1
* **Cloc** : 1

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    7    |    7   |
| Extended Cyclomatic Complexity  |     13   |   13    |
| Cyclomatic complexity           |     12   |  12     |

You can find the corresponding commit [there] and the different file [here] (patch1/).
[there]: https://github.com/android/platform_frameworks_base/commit/5d6d773fab559fdc12e553d60d789f3991ac552c "here"
