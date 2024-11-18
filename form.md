1. Transformace (mùete je libovolnì skládat, pøehazovat, pøidat stejnou BasiCTransformation k více transformacím a kombinovat ji s dalšími, máte pouitı Composit správnì atd.).
	-implementované je mozné akoko¾vek skláda transformácie. bol doimplementovanı návrhovı vzor composite


2. Máte základní testovací scénu s trojúhelníkem.
	-áno 


3. Máte scénu se ètyømi kulièkami a funkèním Phongovım osvìtlovacím modelem.
	-áno	

4. Máte scenu s lesem, kde je více shaderù, více svìtel. Jak modely (stromy, i svìtla) se mohou dynamicky rotovat nebo pohybovat.
	-áno všetko sa môe dynamicky pohybova a rotova
	-zostávajú naimplementova dynamicka rotácia okolo bodu (T',R,T) a dynamicky pohyb na osy XYZ (R', T, R)


5. Máte noèní variantu lesa, kde je lépe vidìt baterka pèi procházení a další typy svìtel.
	-áno
	-pridanı les z smerovım svetlom ale je tam niekde chyba vo vıpoète pravdepodbne svetlo nieje niekde normalizované alebo nieèo.. (niektoré farby sa stratia) mono aj zlı návrh farieb a materialu


+optimalizované VAO o ktorom sme sa bavili na cvièení(jeden model pre mnoho rovnakıch drawableObjectov)