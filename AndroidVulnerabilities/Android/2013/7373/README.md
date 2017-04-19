#CVE-2013-7373
> No patch was found here, may be related to CVE-2013-7372

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2013-7373/ "here"

##Description
Android before 4.4 does not properly arrange for seeding of the OpenSSL PRNG, which makes it easier for attackers to defeat cryptographic protection mechanisms by leveraging use of the PRNG within multiple applications.	

##Additionnal Information
* Version Impacted : Android 1.0 to 4.3.1
* Role of the Component : Cryptography
* Library : Open SSL

##CVSS Score & Vulnerability Types
* Cvss Score : 7.5
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *Partial*
* Availbility Impact : *Partial*
* Access Complexity : *Low*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [200] (http://cwe.mitre.org/data/definitions/200.html) 
