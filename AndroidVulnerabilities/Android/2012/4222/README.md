#CVE-2012-4222
>

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2012-4222/ "here"

##Description
drivers/gpu/msm/kgsl.c in the Qualcomm Innovation Center (QuIC) Graphics KGSL kernel-mode driver for Android 2.3 through 4.2 allows attackers to cause a denial of service (NULL pointer dereference) via an application that uses crafted arguments in a local kgsl_ioctl call.	

##Additionnal Information
* Version Impacted : Android 2.3 to 4.2
* Role of the Component : Driver
* Vendor Specific : Qualcomm 

##CVSS Score & Vulnerability Types
* Cvss Score : 4.3
* CVSS Access : *Network*
* Confidentiality Impact : *None*
* Integrity Impact : *None*
* Availbility Impact : *Partial*
* Access Complexity : *Medium*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [20] (http://cwe.mitre.org/data/definitions/20.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 2
* **Total Commit**: 1
* **Total modified file**: 1 
* **Cloc**: 9



##Patch 
* **Kind of Patch** : Add Condition

####Description
Because we were using _IO_NR, one could construct a malformed ioctl
code that would avoid allocating memory yet go to a function that
expected that memory. Still use _IO_NR to index the array of ioctls,
but check that the full values match before jumping to the helper
function.

CRs-fixed: 385592
Change-Id: Ic0dedbaded469035bd0a2bb0f20fecb2a3045ca5
Signed-off-by: Jordan Crouse <jcrouse@codeaurora.org>


####Origin
* Language : CPP
* Origin of the issue : Code ->  Input Not Verified
* Location : [kernel/msn] (https://www.codeaurora.org/cgit/quic/la/kernel/msm/)


You can find here [the corresponding commit] (https://www.codeaurora.org/cgit/quic/la//kernel/msm/commit/?id=1e76f61bb001b93795a227f8f808104b6c10b048)  and the different file [in this folder] (patch/).
