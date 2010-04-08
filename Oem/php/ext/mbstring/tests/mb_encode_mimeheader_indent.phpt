--TEST--
Test mb_encode_mimeheader() function : basic functionality, indent
--SKIPIF--
<?php
extension_loaded('mbstring') or die('skip');
function_exists('mb_encode_mimeheader') or die("skip mb_encode_mimeheader() is not available in this build");
?>

--FILE--
<?php
/* Prototype  : string mb_encode_mimeheader
 * (string $str [, string $charset [, string $transfer_encoding [, string $linefeed [, int $indent]]]])
 * Description: Converts the string to MIME "encoded-word" in the format of =?charset?(B|Q)?encoded_string?= 
 * Source code: ext/mbstring/mbstring.c
 */

/*
 * Pass different data types to $indent argument to see how mb_encode_mimeheader() behaves
 */

echo "*** Testing mb_encode_mimeheader() : indent ***\n";

mb_internal_encoding('utf-8');

// Initialise function arguments not being substituted
$str = base64_decode('zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==');
$charset = 'utf-8';
$linefeed = "\r\n";

for ($i = 0; $i < 100; $i++) {
  echo "\n-- Iteration $i --\n";
  var_dump( mb_encode_mimeheader($str, $charset, "B", $linefeed, $i));
  var_dump( mb_encode_mimeheader($str, $charset, "Q", $linefeed, $i));  
};
echo "Done";
?>
--EXPECT--
*** Testing mb_encode_mimeheader() : indent ***

-- Iteration 0 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 1 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 2 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 3 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 4 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrU=?=
 =?UTF-8?B?zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9?=
 =?UTF-8?Q?=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA?=
 =?UTF-8?Q?=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36?=
 =?UTF-8?Q?=37=38=39=2E?="

-- Iteration 5 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrU=?=
 =?UTF-8?B?zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9?=
 =?UTF-8?Q?=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA?=
 =?UTF-8?Q?=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36?=
 =?UTF-8?Q?=37=38=39=2E?="

-- Iteration 6 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrU=?=
 =?UTF-8?B?zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9?=
 =?UTF-8?Q?=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA?=
 =?UTF-8?Q?=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36?=
 =?UTF-8?Q?=37=38=39=2E?="

-- Iteration 7 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrU=?=
 =?UTF-8?B?zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1?=
 =?UTF-8?Q?=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20?=
 =?UTF-8?Q?=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34?=
 =?UTF-8?Q?=35=36=37=38=39=2E?="

-- Iteration 8 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66?=
 =?UTF-8?B?zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1?=
 =?UTF-8?Q?=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20?=
 =?UTF-8?Q?=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34?=
 =?UTF-8?Q?=35=36=37=38=39=2E?="

-- Iteration 9 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66?=
 =?UTF-8?B?zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1?=
 =?UTF-8?Q?=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20?=
 =?UTF-8?Q?=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34?=
 =?UTF-8?Q?=35=36=37=38=39=2E?="

-- Iteration 10 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66?=
 =?UTF-8?B?zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1?=
 =?UTF-8?Q?=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20?=
 =?UTF-8?Q?=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34?=
 =?UTF-8?Q?=35=36=37=38=39=2E?="

-- Iteration 11 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66?=
 =?UTF-8?B?zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1?=
 =?UTF-8?Q?=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20?=
 =?UTF-8?Q?=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34?=
 =?UTF-8?Q?=35=36=37=38=39=2E?="

-- Iteration 12 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+M?=
 =?UTF-8?B?IM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1?=
 =?UTF-8?Q?=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20?=
 =?UTF-8?Q?=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34?=
 =?UTF-8?Q?=35=36=37=38=39=2E?="

-- Iteration 13 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+M?=
 =?UTF-8?B?IM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD?=
 =?UTF-8?Q?=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C?=
 =?UTF-8?Q?=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33?=
 =?UTF-8?Q?=34=35=36=37=38=39=2E?="

-- Iteration 14 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+M?=
 =?UTF-8?B?IM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD?=
 =?UTF-8?Q?=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C?=
 =?UTF-8?Q?=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33?=
 =?UTF-8?Q?=34=35=36=37=38=39=2E?="

-- Iteration 15 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+M?=
 =?UTF-8?B?IM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD?=
 =?UTF-8?Q?=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C?=
 =?UTF-8?Q?=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33?=
 =?UTF-8?Q?=34=35=36=37=38=39=2E?="

-- Iteration 16 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrk=?=
 =?UTF-8?B?zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD?=
 =?UTF-8?Q?=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C?=
 =?UTF-8?Q?=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33?=
 =?UTF-8?Q?=34=35=36=37=38=39=2E?="

-- Iteration 17 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrk=?=
 =?UTF-8?B?zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD?=
 =?UTF-8?Q?=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C?=
 =?UTF-8?Q?=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33?=
 =?UTF-8?Q?=34=35=36=37=38=39=2E?="

-- Iteration 18 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrk=?=
 =?UTF-8?B?zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD?=
 =?UTF-8?Q?=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C?=
 =?UTF-8?Q?=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33?=
 =?UTF-8?Q?=34=35=36=37=38=39=2E?="

-- Iteration 19 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrk=?=
 =?UTF-8?B?zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF?=
 =?UTF-8?Q?=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA?=
 =?UTF-8?Q?=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31?=
 =?UTF-8?Q?=32=33=34=35=36=37=38=39=2E?="

-- Iteration 20 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869?=
 =?UTF-8?B?zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF?=
 =?UTF-8?Q?=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA?=
 =?UTF-8?Q?=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31?=
 =?UTF-8?Q?=32=33=34=35=36=37=38=39=2E?="

-- Iteration 21 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869?=
 =?UTF-8?B?zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF?=
 =?UTF-8?Q?=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA?=
 =?UTF-8?Q?=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31?=
 =?UTF-8?Q?=32=33=34=35=36=37=38=39=2E?="

-- Iteration 22 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869?=
 =?UTF-8?B?zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF?=
 =?UTF-8?Q?=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA?=
 =?UTF-8?Q?=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31?=
 =?UTF-8?Q?=32=33=34=35=36=37=38=39=2E?="

-- Iteration 23 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869?=
 =?UTF-8?B?zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF?=
 =?UTF-8?Q?=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA?=
 =?UTF-8?Q?=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31?=
 =?UTF-8?Q?=32=33=34=35=36=37=38=39=2E?="

-- Iteration 24 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrs=?=
 =?UTF-8?B?zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF?=
 =?UTF-8?Q?=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA?=
 =?UTF-8?Q?=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31?=
 =?UTF-8?Q?=32=33=34=35=36=37=38=39=2E?="

-- Iteration 25 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrs=?=
 =?UTF-8?B?zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9?=
 =?UTF-8?Q?=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20?=
 =?UTF-8?Q?=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 26 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrs=?=
 =?UTF-8?B?zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9?=
 =?UTF-8?Q?=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20?=
 =?UTF-8?Q?=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 27 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrs=?=
 =?UTF-8?B?zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9?=
 =?UTF-8?Q?=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20?=
 =?UTF-8?Q?=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 28 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67?=
 =?UTF-8?B?zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9?=
 =?UTF-8?Q?=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20?=
 =?UTF-8?Q?=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 29 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67?=
 =?UTF-8?B?zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9?=
 =?UTF-8?Q?=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20?=
 =?UTF-8?Q?=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 30 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67?=
 =?UTF-8?B?zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9?=
 =?UTF-8?Q?=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20?=
 =?UTF-8?Q?=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 31 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67?=
 =?UTF-8?B?zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20?=
 =?UTF-8?Q?=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD?=
 =?UTF-8?Q?=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF?=
 =?UTF-8?Q?=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 32 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSA=?=
 =?UTF-8?B?zrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20?=
 =?UTF-8?Q?=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD?=
 =?UTF-8?Q?=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF?=
 =?UTF-8?Q?=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 33 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSA=?=
 =?UTF-8?B?zrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20?=
 =?UTF-8?Q?=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD?=
 =?UTF-8?Q?=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF?=
 =?UTF-8?Q?=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 34 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSA=?=
 =?UTF-8?B?zrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20?=
 =?UTF-8?Q?=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD?=
 =?UTF-8?Q?=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF?=
 =?UTF-8?Q?=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 35 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSA=?=
 =?UTF-8?B?zrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20?=
 =?UTF-8?Q?=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD?=
 =?UTF-8?Q?=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF?=
 =?UTF-8?Q?=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 36 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrE=?=
 =?UTF-8?B?zrkgzrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4?=
 =?UTF-8?B?OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20?=
 =?UTF-8?Q?=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD?=
 =?UTF-8?Q?=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF?=
 =?UTF-8?Q?=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 37 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrE=?=
 =?UTF-8?B?zrkgzrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4?=
 =?UTF-8?B?OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C?=
 =?UTF-8?Q?=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7?=
 =?UTF-8?Q?=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD?=
 =?UTF-8?Q?=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 38 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrE=?=
 =?UTF-8?B?zrkgzrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4?=
 =?UTF-8?B?OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C?=
 =?UTF-8?Q?=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7?=
 =?UTF-8?Q?=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD?=
 =?UTF-8?Q?=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 39 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrE=?=
 =?UTF-8?B?zrkgzrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEyMzQ1Njc4?=
 =?UTF-8?B?OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C?=
 =?UTF-8?Q?=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB=CE=B7?=
 =?UTF-8?Q?=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5=CE=BD?=
 =?UTF-8?Q?=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 40 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869?=
 =?UTF-8?B?zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2?=
 =?UTF-8?B?Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84?=
 =?UTF-8?Q?=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB?=
 =?UTF-8?Q?=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5?=
 =?UTF-8?Q?=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 41 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869?=
 =?UTF-8?B?zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2?=
 =?UTF-8?B?Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84?=
 =?UTF-8?Q?=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB?=
 =?UTF-8?Q?=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5?=
 =?UTF-8?Q?=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 42 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869?=
 =?UTF-8?B?zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2?=
 =?UTF-8?B?Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84?=
 =?UTF-8?Q?=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB?=
 =?UTF-8?Q?=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5?=
 =?UTF-8?Q?=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 43 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869?=
 =?UTF-8?B?zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAwMTIzNDU2?=
 =?UTF-8?B?Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84?=
 =?UTF-8?Q?=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB?=
 =?UTF-8?Q?=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5?=
 =?UTF-8?Q?=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 44 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrU=?=
 =?UTF-8?B?zq/Ovc6xzrkgzrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEy?=
 =?UTF-8?B?MzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84?=
 =?UTF-8?Q?=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB?=
 =?UTF-8?Q?=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5?=
 =?UTF-8?Q?=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 45 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrU=?=
 =?UTF-8?B?zq/Ovc6xzrkgzrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEy?=
 =?UTF-8?B?MzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84?=
 =?UTF-8?Q?=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB=CE=BB?=
 =?UTF-8?Q?=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC=CE=B5?=
 =?UTF-8?Q?=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 46 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrU=?=
 =?UTF-8?B?zq/Ovc6xzrkgzrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEy?=
 =?UTF-8?B?MzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85?=
 =?UTF-8?Q?=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB?=
 =?UTF-8?Q?=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC?=
 =?UTF-8?Q?=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 47 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wgzrU=?=
 =?UTF-8?B?zq/Ovc6xzrkgzrXOu867zrfOvc65zrrPjCDOus61zq/OvM61zr3Ovy4gMDEy?=
 =?UTF-8?B?MzQ1Njc4OS4=?="
string(249) "=?UTF-8?Q?=CE=91=CF=85?=
 =?UTF-8?Q?=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB?=
 =?UTF-8?Q?=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC?=
 =?UTF-8?Q?=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 48 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wg?=
 =?UTF-8?B?zrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAw?=
 =?UTF-8?B?MTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85?=
 =?UTF-8?Q?=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB?=
 =?UTF-8?Q?=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC?=
 =?UTF-8?Q?=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 49 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wg?=
 =?UTF-8?B?zrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAw?=
 =?UTF-8?B?MTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85?=
 =?UTF-8?Q?=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB?=
 =?UTF-8?Q?=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC?=
 =?UTF-8?Q?=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 50 --
string(130) "=?UTF-8?B?zpHPhc+Ez4wg?=
 =?UTF-8?B?zrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868zrXOvc6/LiAw?=
 =?UTF-8?B?MTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85?=
 =?UTF-8?Q?=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20=CE=B5=CE=BB?=
 =?UTF-8?Q?=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5=CE=AF=CE=BC?=
 =?UTF-8?Q?=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38=39=2E?="

-- Iteration 51 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 52 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 53 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 54 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 55 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 56 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 57 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 58 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 59 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 60 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 61 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 62 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 63 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 64 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 65 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 66 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 67 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 68 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 69 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 70 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 71 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 72 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 73 --
string(118) "
 =?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(252) "
 =?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 74 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 75 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 76 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 77 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 78 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 79 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 80 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 81 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 82 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 83 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 84 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 85 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 86 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 87 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 88 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 89 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 90 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 91 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 92 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 93 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 94 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 95 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 96 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 97 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 98 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="

-- Iteration 99 --
string(115) "=?UTF-8?B?zpHPhc+Ez4wgzrXOr869zrHOuSDOtc67zrvOt869zrnOus+MIM66zrXOr868?=
 =?UTF-8?B?zrXOvc6/LiAwMTIzNDU2Nzg5Lg==?="
string(249) "=?UTF-8?Q?=CE=91=CF=85=CF=84=CF=8C=20=CE=B5=CE=AF=CE=BD=CE=B1=CE=B9=20?=
 =?UTF-8?Q?=CE=B5=CE=BB=CE=BB=CE=B7=CE=BD=CE=B9=CE=BA=CF=8C=20=CE=BA=CE=B5?=
 =?UTF-8?Q?=CE=AF=CE=BC=CE=B5=CE=BD=CE=BF=2E=20=30=31=32=33=34=35=36=37=38?=
 =?UTF-8?Q?=39=2E?="
Done

