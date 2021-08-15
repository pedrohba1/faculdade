
library ieee;
use ieee.std_logic_1164.all;

-------------------------------------------------

entity Mux is
port(	I3: 	in std_logic_vector(7 downto 0);
	I2: 	in std_logic_vector(7 downto 0);
	I1: 	in std_logic_vector(7 downto 0);
	I0: 	in std_logic_vector(7 downto 0);
	S:	in std_logic_vector(1 downto 0);
	O:	out std_logic_vector(7 downto 0)
);
end Mux;  

-------------------------------------------------

architecture behv2 of Mux is
begin

    O <=	I0 when S="00" else
		I1 when S="01" else
		I2 when S="10" else
		I3 when S="11" else
		"ZZZZZZZZ";

end behv2;
--------------------------------------------------