-- preciso baixar a versão 10.1d
library ieee;
use ieee.std_logic_1164.all;

-------------------------------------------------

architecture TB of tb_mux is 
    signed T_I3 std_logic_vector(7 donwto 0) = "00000000";
    signed T_I2 std_logic_vecto(7 donwto 0) = "00000000";
    signed T_I3 std_logic_vecto(7 donwto 0) = "00000000";
    signed T_S std_logic_vecto(1 donwto 0);
    signed T_O std_logic_vector(7 downto 0);
    

    

    component Mux
    port(	I3: 	in std_logic_vector(7 downto 0);
		I2: 	in std_logic_vector(7 downto 0);
		I1: 	in std_logic_vector(7 downto 0);
		I0: 	in std_logic_vector(7 downto 0);
		S:	in std_logic_vector(1 downto 0);
		O:	out std_logic_vector(7 downto 0)
    );
    end component;

begin
    
    
 U_Mux: Mux port map (T_I3, T_I2, T_I1, T_I0, T_S, T_O);
	
    process							
	
	variable err_cnt: integer :=0;
	
    begin								
			 	
	T_I3 <= "00000001";		-- I0-I3 are different signals
	T_I2 <= "00000010";
	T_I1 <= "00000011";
	T_I0 <= "00000111";
		
	-- case select eqaul "00"
	wait for 10 ns;	
	T_S <= "00";	
	wait for 1 ns;
	assert (T_O="00000111") report "Error Case 0" severity error;
	if (T_O/="00000111") then 
	    err_cnt := err_cnt+1;
	end if;
		
	-- case select equal "01"
	wait for 10 ns;
	T_S <= "01";	  
	wait for 1 ns;
	assert (T_O="00000011") report "Error Case 1" severity error;
	if (T_O/="00000011") then 
	    err_cnt := err_cnt+1;
	end if;
		
	-- case select equal "10"
	wait for 10 ns;
	T_S <= "10";	  
	wait for 1 ns;
	assert (T_O="00000010") report "Error Case 2" severity error;
	if (T_O/="00000010") then 
	    err_cnt := err_cnt+1;
	end if;		
			
	-- case select equal "11"
	wait for 10 ns;
	T_S <= "11";	  
	wait for 1 ns;
	assert (T_O="00000001") report "Error Case 3" severity error;		
	if (T_O/="00000001") then 
	    err_cnt := err_cnt+1;
	end if;
			
	-- case equal "11"
	wait for 10 ns;
	T_S <= "UU";

	-- summary of all the tests
	if (err_cnt=0) then
	    assert (false) 
	    report "Testbench of Mux completed sucessfully!"
	    severity note;
	else
	    assert (true)
	    report "Something wrong, try again!"
	    severity error;
	end if;
		
	wait;
    
    end process;

end TB;