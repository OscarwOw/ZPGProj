1. Transformace (m��ete je libovoln� skl�dat, p�ehazovat, p�idat stejnou BasiCTransformation k v�ce transformac�m a kombinovat ji s dal��mi, m�te pou�it� Composit spr�vn� atd.).
	-implementovan� je mozn� akoko�vek skl�da� transform�cie. bol doimplementovan� n�vrhov� vzor composite


2. M�te z�kladn� testovac� sc�nu s troj�heln�kem.
	-�no 


3. M�te sc�nu se �ty�mi kuli�kami a funk�n�m Phongov�m osv�tlovac�m modelem.
	-�no	

4. M�te scenu s lesem, kde je v�ce shader�, v�ce sv�tel. Jak modely (stromy, i sv�tla) se mohou dynamicky rotovat nebo pohybovat.
	-�no v�etko sa m��e dynamicky pohybova� a rotova�
	-zost�vaj� naimplementova� dynamicka rot�cia okolo bodu (T',R,T) a dynamicky pohyb na osy XYZ (R', T, R)


5. M�te no�n� variantu lesa, kde je l�pe vid�t baterka p�i proch�zen� a dal�� typy sv�tel.
	-�no
	-pridan� les z smerov�m svetlom ale je tam niekde chyba vo v�po�te pravdepodbne svetlo nieje niekde normalizovan� alebo nie�o.. (niektor� farby sa stratia) mo�no aj zl� n�vrh farieb a materialu


+optimalizovan� VAO o ktorom sme sa bavili na cvi�en�(jeden model pre mnoho rovnak�ch drawableObjectov)