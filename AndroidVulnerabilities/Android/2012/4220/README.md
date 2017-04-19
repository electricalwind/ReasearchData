#CVE-2012-4220
>One issue found with the same patch as [CVE-2012-4221](../4221/README.md)

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2012-4220/ "here"

##Description
diagchar_core.c in the Qualcomm Innovation Center (QuIC) Diagnostics (aka DIAG) kernel-mode driver for Android 2.3 through 4.2 allows attackers to execute arbitrary code or cause a denial of service (incorrect pointer dereference) via an application that uses crafted arguments in a local diagchar_ioctl call.	

##Additionnal Information
* Version Impacted : Android 2.3 to 4.2
* Role of the Component : Driver
* Vendor Specific : Qualcomm

##CVSS Score & Vulnerability Types
* Cvss Score : 6.8
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *Partial*
* Availbility Impact : *Partial*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : N.C

##Corresponding Issue
###Complexity
* **Cycc total**: N.C >20
* **Total Commit**: 1
* **Total modified file**: 2
* **Cloc**: 57


####Origin
* Language : CPP
* Origin of the issue :  Incorrect pointer dereference & Integer overflow
* Location : [kernel/msn] (https://www.codeaurora.org/cgit/quic/la/kernel/msm/)

####Patch
* **Kind of Patch** : Rewrite Function/Add Condition


You can find here [the corresponding commit] (https://www.codeaurora.org/cgit/quic/la/kernel/msm/diff/?id=32682d16fb46a60a7952c4d9e0653602ff674e4b)  and the different file [in this folder] (patch/).
