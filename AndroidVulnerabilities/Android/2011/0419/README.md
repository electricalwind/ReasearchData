#CVE-2011-0419
>1 issue found with one commit.

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2011-0419/ "here"

##Description
Stack consumption vulnerability in the fnmatch implementation in apr_fnmatch.c in the Apache Portable Runtime (APR) library before 1.4.3 and the Apache HTTP Server before 2.2.18, and in fnmatch.c in libc in NetBSD 5.1, OpenBSD 4.8, FreeBSD, Apple Mac OS X 10.6, Oracle Solaris 10, and Android, allows context-dependent attackers to cause a denial of service (CPU and memory consumption) via *? sequences in the first argument, as demonstrated by attacks against mod_autoindex in httpd.

##Additionnal Information
* Role of the Component : Library
* Tiers Library

##CVSS Score & Vulnerability Types
* Cvss Score : 4.3
* CVSS Access : *Network*
* Confidentiality Impact : *None*
* Integrity Impact : *None*
* Availbility Impact : *Partial*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [399] (http://cwe.mitre.org/data/definitions/399.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: N.C
* **Total Commit**: 1
* **Total modified file**: 1
* **Cloc**: N.F


###Patch 
####Description
Security: CVE-2011-0419
Reported by: Maksymilian Arciemowicz <cxib securityreason.com>

Excessive CPU consumption was possible due to the unconstrained, recursive 
invocation of apr_fnmatch, as apr_fnmatch processed '*' wildcards.

Introduce new apr_fnmatch implementation.  This delivers optimizations 
in some common cases, without the underlying weakness of recursion 
present in older implementations.


####Origin
* Language : C 
* Origin of the issue : Code -> Resource Management -> Stack Consumption
* Location : [svn/apache] (http://svn.apache.org)


####Patch 
* **Kind of Patch** : Complete Rewrite
* **Cycc** : N.C
* **Cloc** : >100

You can find here [the corresponding commit] (http://svn.apache.org/viewvc?view=revision&revision=1098188)  and the patch file [here] (patch1/) 


