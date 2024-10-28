library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity nanosecond_counter is
    Port (
        -- AXI4-Lite signals
        s_axi_aclk     : in  STD_LOGIC;
        s_axi_aresetn  : in  STD_LOGIC;
        s_axi_awaddr   : in  STD_LOGIC_VECTOR(3 downto 0);
        s_axi_awvalid  : in  STD_LOGIC;
        s_axi_awready  : out STD_LOGIC;
        s_axi_wdata    : in  STD_LOGIC_VECTOR(31 downto 0);
        s_axi_wstrb    : in  STD_LOGIC_VECTOR(3 downto 0);
        s_axi_wvalid   : in  STD_LOGIC;
        s_axi_wready   : out STD_LOGIC;
        s_axi_bresp    : out STD_LOGIC_VECTOR(1 downto 0);
        s_axi_bvalid   : out STD_LOGIC;
        s_axi_bready   : in  STD_LOGIC;
        s_axi_araddr   : in  STD_LOGIC_VECTOR(3 downto 0);
        s_axi_arvalid  : in  STD_LOGIC;
        s_axi_arready  : out STD_LOGIC;
        s_axi_rdata    : out STD_LOGIC_VECTOR(31 downto 0);
        s_axi_rresp    : out STD_LOGIC_VECTOR(1 downto 0);
        s_axi_rvalid   : out STD_LOGIC;
        s_axi_rready   : in  STD_LOGIC;

        -- Counter clock input
        clk            : in  STD_LOGIC
    );
end nanosecond_counter;

architecture Behavioral of nanosecond_counter is
    -- Counter signal
    signal counter_reg : unsigned(31 downto 0) := (others => '0');
    
    -- AXI4-Lite interface signals
    signal axi_awready_int, axi_wready_int, axi_bvalid_int, axi_arready_int, axi_rvalid_int : STD_LOGIC := '0';
    signal axi_rdata_int : STD_LOGIC_VECTOR(31 downto 0) := (others => '0');

    -- Constant for the maximum counter value (100,000,000)
    constant MAX_COUNT : unsigned(31 downto 0) := to_unsigned(100000000, 32);

begin
    -- Counter Process
    process(clk)
    begin
        if rising_edge(clk) then
            if counter_reg = MAX_COUNT then
                -- Reset counter when it reaches 100,000,000
                counter_reg <= (others => '0');
            else
                -- Increment counter
                counter_reg <= counter_reg + 1;
            end if;
        end if;
    end process;

    -- AXI4-Lite Write Process
    process(s_axi_aclk)
    begin
        if rising_edge(s_axi_aclk) then
            if s_axi_aresetn = '0' then
                axi_awready_int <= '0';
                axi_wready_int <= '0';
                axi_bvalid_int <= '0';
                counter_reg <= (others => '0'); -- Reset the counter on reset
            else
                if s_axi_awvalid = '1' and axi_awready_int = '0' then
                    axi_awready_int <= '1';
                elsif s_axi_awvalid = '0' then
                    axi_awready_int <= '0';
                end if;

                if s_axi_wvalid = '1' and axi_wready_int = '0' then
                    axi_wready_int <= '1';

                    -- Write to the counter reset register
                    if s_axi_awaddr = "0000" then
                        if s_axi_wdata(0) = '1' then
                            counter_reg <= (others => '0'); -- Reset counter
                        end if;
                    end if;
                elsif s_axi_wvalid = '0' then
                    axi_wready_int <= '0';
                end if;

                if axi_awready_int = '1' and axi_wready_int = '1' then
                    axi_bvalid_int <= '1';
                elsif s_axi_bready = '1' then
                    axi_bvalid_int <= '0';
                end if;
            end if;
        end if;
    end process;

    -- AXI4-Lite Read Process
    process(s_axi_aclk)
    begin
        if rising_edge(s_axi_aclk) then
            if s_axi_aresetn = '0' then
                axi_arready_int <= '0';
                axi_rvalid_int <= '0';
                axi_rdata_int <= (others => '0');
            else
                if s_axi_arvalid = '1' and axi_arready_int = '0' then
                    axi_arready_int <= '1';

                    -- Read the counter value
                    if s_axi_araddr = "0000" then
                        axi_rdata_int <= std_logic_vector(counter_reg);
                    else
                        axi_rdata_int <= (others => '0');
                    end if;
                elsif s_axi_arvalid = '0' then
                    axi_arready_int <= '0';
                end if;

                if axi_arready_int = '1' then
                    axi_rvalid_int <= '1';
                elsif s_axi_rready = '1' then
                    axi_rvalid_int <= '0';
                end if;
            end if;
        end if;
    end process;

    -- Output assignments
    s_axi_awready <= axi_awready_int;
    s_axi_wready <= axi_wready_int;
    s_axi_bvalid <= axi_bvalid_int;
    s_axi_bresp <= "00"; -- OKAY response
    s_axi_arready <= axi_arready_int;
    s_axi_rvalid <= axi_rvalid_int;
    s_axi_rresp <= "00"; -- OKAY response
    s_axi_rdata <= axi_rdata_int;

end Behavioral;
