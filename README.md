# Schnorr-Signature-Implmented-By-C
說明：
使用語言：C
外部函式庫：GNU MP、PicoSHA256(https://github.com/okdshin/PicoSHA2)
a.變數命名
	˙p、q、g為公開參數
	˙y為public key
	˙x為private key
	˙k為簽章過程選擇的亂數，r為透過k計算得到之值
	˙(e,s) 為簽章
b.檔案名稱
	˙parameter.txt 包含公開參數、公開金鑰、私密金鑰
	˙user.txt 包含欲簽章之文檔，最大可讀取256個字元
	˙Signature.txt 包含簽章
	˙Verification.txt 用來驗證
	˙readme.txt 用來說明程式使用方法

