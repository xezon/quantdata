
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <common/enum.h>
#include <common/util.h>
#include <common/utf8.h>
#include <utility>
#include <array>
#include <vector>

namespace quantdata {
namespace internal {

using Tchar = utility::char_t;
using TWebString = const Tchar*;
using TStringA = std::string;
using TStringW = std::wstring;

template <typename Element, size_t Size>
struct FixedArrayStruct
{
	using array_type = ::std::array<Element, Size>;
	using size_type = typename array_type::size_type;
	using reference = typename array_type::reference;
	using const_reference = typename array_type::const_reference;
	template <class... Args>
	constexpr FixedArrayStruct(Args&&... args) noexcept
		: array({std::forward<Args>(args)...})
	{
		static_assert(sizeof...(args) == Size,
			"Argument count must match array count");
	}
	const_reference operator[](size_type i) const {
		return array[i];
	}
	const array_type array;
};

template <typename Element>
struct FixedVectorStruct
{
	using array_type = ::std::vector<Element>;
	using size_type = typename array_type::size_type;
	using reference = typename array_type::reference;
	using const_reference = typename array_type::const_reference;
	template <class... Args>
	constexpr FixedVectorStruct(Args&&... args) noexcept
		: array({std::forward<Args>(args)...})
	{}
	const_reference operator[](size_type i) const {
		return array[i];
	}
	const array_type array;
};

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// PROVIDER URL /////////////////////////////////////////

using TProviderUrls = FixedArrayStruct<TWebString, CQuantDataProvider::count()>;

constexpr TProviderUrls g_providerUrls(
	/* Quandl        */ U("https://www.quandl.com/"          ),
	/* Oanda         */ U("https://api-fxtrade.oanda.com/"   ),
	/* OandaPractice */ U("https://api-fxpractice.oanda.com/"),
	/* AlphaVantage  */ U("https://www.alphavantage.co/"     ),
	/* OpenExchange  */ U("https://openexchangerates.org/"   ),
	/* TrueFx        */ U("https://www.truefx.com/"          )
);

inline const TProviderUrls& GetProviderUrls()
{
	return g_providerUrls;
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// PERIOD NAMES /////////////////////////////////////////

using TProviderPeriodNamesX = FixedArrayStruct<TWebString, CQuantDataProvider::count()>;
using TPeriodNamesX         = FixedArrayStruct<TProviderPeriodNamesX, CQuantDataPeriod::count()>;

constexpr TWebString UnnamedPeriod = U("!");
constexpr TPeriodNamesX g_periodNamesX(
	/* Finest   */ TProviderPeriodNamesX( U("none"     ) , U("S5" ), U("S5" ) , U("1min"    ) , U("1m" ) , UnnamedPeriod ),
	/* Second5  */ TProviderPeriodNamesX( U(""         ) , U("S5" ), U("S5" ) , U(""        ) , U(""   ) , U(""        ) ),
	/* Second10 */ TProviderPeriodNamesX( U(""         ) , U("S10"), U("S10") , U(""        ) , U(""   ) , U(""        ) ),
	/* Second15 */ TProviderPeriodNamesX( U(""         ) , U("S15"), U("S15") , U(""        ) , U(""   ) , U(""        ) ),
	/* Second30 */ TProviderPeriodNamesX( U(""         ) , U("S30"), U("S30") , U(""        ) , U(""   ) , U(""        ) ),
	/* Minute   */ TProviderPeriodNamesX( U(""         ) , U("M1" ), U("M1" ) , U("1min"    ) , U("1m" ) , U(""        ) ),
	/* Minute2  */ TProviderPeriodNamesX( U(""         ) , U("M2" ), U("M2" ) , U(""        ) , U(""   ) , U(""        ) ),
	/* Minute4  */ TProviderPeriodNamesX( U(""         ) , U("M4" ), U("M4" ) , U(""        ) , U(""   ) , U(""        ) ),
	/* Minute5  */ TProviderPeriodNamesX( U(""         ) , U("M5" ), U("M5" ) , U("5min"    ) , U("5m" ) , U(""        ) ),
	/* Minute10 */ TProviderPeriodNamesX( U(""         ) , U("M10"), U("M10") , U(""        ) , U(""   ) , U(""        ) ),
	/* Minute15 */ TProviderPeriodNamesX( U(""         ) , U("M15"), U("M15") , U("15min"   ) , U("15m") , U(""        ) ),
	/* Minute30 */ TProviderPeriodNamesX( U(""         ) , U("M30"), U("M30") , U("30min"   ) , U("30m") , U(""        ) ),
	/* Hour     */ TProviderPeriodNamesX( U(""         ) , U("H1" ), U("H1" ) , U("60min"   ) , U("1h" ) , U(""        ) ),
	/* Hour2    */ TProviderPeriodNamesX( U(""         ) , U("H2" ), U("H2" ) , U(""        ) , U(""   ) , U(""        ) ),
	/* Hour3    */ TProviderPeriodNamesX( U(""         ) , U("H3" ), U("H3" ) , U(""        ) , U(""   ) , U(""        ) ),
	/* Hour4    */ TProviderPeriodNamesX( U(""         ) , U("H4" ), U("H4" ) , U(""        ) , U(""   ) , U(""        ) ),
	/* Hour6    */ TProviderPeriodNamesX( U(""         ) , U("H6" ), U("H6" ) , U(""        ) , U(""   ) , U(""        ) ),
	/* Hour8    */ TProviderPeriodNamesX( U(""         ) , U("H8" ), U("H8" ) , U(""        ) , U(""   ) , U(""        ) ),
	/* Hour12   */ TProviderPeriodNamesX( U(""         ) , U("H12"), U("H12") , U(""        ) , U("12h") , U(""        ) ),
	/* Day      */ TProviderPeriodNamesX( U("daily"    ) , U("D"  ), U("D"  ) , UnnamedPeriod , U("1d" ) , U(""        ) ),
	/* Week     */ TProviderPeriodNamesX( U("weekly"   ) , U("W"  ), U("W"  ) , UnnamedPeriod , U("1w" ) , U(""        ) ),
	/* Month    */ TProviderPeriodNamesX( U("monthly"  ) , U("M"  ), U("M"  ) , UnnamedPeriod , U("1mo") , U(""        ) ),
	/* Quarter  */ TProviderPeriodNamesX( U("quarterly") , U(""   ), U(""   ) , U(""        ) , U(""   ) , U(""        ) ),
	/* Annual   */ TProviderPeriodNamesX( U("annual"   ) , U(""   ), U(""   ) , U(""        ) , U(""   ) , U(""        ) )
);

inline const TPeriodNamesX& GetPeriodNamesX()
{
	return g_periodNamesX;
}

using TSupportedPeriods         = std::vector<TQuantDataPeriod>;
using TProviderSupportedPeriods = std::array<TSupportedPeriods, CQuantDataProvider::count()>;

inline TProviderSupportedPeriods BuildProviderSupportedPeriods()
{
	TProviderSupportedPeriods providerArray;
	for (CQuantDataProvider provider : CQuantDataProvider())
	{
		const auto providerOrdinal = provider.ordinal();
		TSupportedPeriods& periods = providerArray[providerOrdinal];

		for (CQuantDataPeriod period : CQuantDataPeriod())
		{
			const auto periodOrdinal = period.ordinal();
			TWebString apiName = g_periodNamesX[periodOrdinal][providerOrdinal];

			if (util::is_valid_string(apiName))
			{
				const auto value = period.value();
				periods.push_back(value);
			}
		}
	}
	return providerArray;
}

using TPeriodNames         = std::array<TWebString, CQuantDataPeriod::count()>;
using TProviderPeriodNames = std::array<TPeriodNames, CQuantDataProvider::count()>;

inline TProviderPeriodNames BuildProviderPeriodNames()
{
	TProviderPeriodNames providerArray = {};
	for (CQuantDataProvider provider : CQuantDataProvider())
	{
		const auto providerOrdinal = provider.ordinal();
		TPeriodNames& nameArray = providerArray[providerOrdinal];

		for (CQuantDataPeriod period : CQuantDataPeriod())
		{
			const auto periodOrdinal = period.ordinal();
			TWebString apiName = g_periodNamesX[periodOrdinal][providerOrdinal];
			nameArray[periodOrdinal] = apiName;
		}
	}
	return providerArray;
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// SYMBOL SOURCE ////////////////////////////////////////

enum class ESymbolSourceFormat { json, csv };
enum class ESymbolSourceFlags
{
	None = 0,
	RequireAuth = 1<<0,
};
DEFINE_ENUM_BIT_OPERATORS(ESymbolSourceFlags);
DEFINE_ENUM_COMP_OPERATORS(ESymbolSourceFlags);

struct SSymbolSource
{
	SSymbolSource() noexcept
		: query(U(""))
		, format(ESymbolSourceFormat::json)
		, flags(ESymbolSourceFlags::None)
		, csv()
	{}
	template <class Function>
	SSymbolSource(
		TWebString query,
		ESymbolSourceFormat format,
		ESymbolSourceFlags flags,
		Function function) noexcept
		: query(query)
		, format(format)
		, flags(flags)
		, csv()
	{
		function(*this);
	}
	TWebString const query;
	const ESymbolSourceFormat format;
	const ESymbolSourceFlags flags;
	json::csv_parameters csv;
};

using TSymbolSources         = std::vector<SSymbolSource>;
using TProviderSymbolSources = std::array<TSymbolSources, CQuantDataProvider::count()>;

inline void AddSymbolUrls(TProviderSymbolSources& instance, CQuantDataProvider provider, const SSymbolSource& symbolSource)
{
	TSymbolSources& symbolSources = instance[provider.ordinal()];
	symbolSources.resize(symbolSources.size() + 1, symbolSource);
}

inline TProviderSymbolSources BuildProviderSymbolSources()
{
	TProviderSymbolSources instance;
	AddSymbolUrls(instance,
		CQuantDataProvider::Oanda,
		SSymbolSource(U("v20/instruments/"),
			ESymbolSourceFormat::json,
			ESymbolSourceFlags::RequireAuth,
			[](SSymbolSource&) {}
		)
	);
	AddSymbolUrls(instance,
		CQuantDataProvider::OandaPractice,
		SSymbolSource(U("v20/instruments/"),
			ESymbolSourceFormat::json,
			ESymbolSourceFlags::RequireAuth,
			[](SSymbolSource&) {}
		)
	);
	AddSymbolUrls(instance,
		CQuantDataProvider::AlphaVantage,
		SSymbolSource(U("digital_currency_list/"),
			ESymbolSourceFormat::csv,
			ESymbolSourceFlags::None,
			[](SSymbolSource& obj) {
				obj.csv
				.column_types("string,string")
				.column_names("name,desc")
				.header_lines(1)
				.assume_header(true)
				.ignore_empty_lines(true); }
		)
	);
	AddSymbolUrls(instance,
		CQuantDataProvider::AlphaVantage,
		SSymbolSource(U("physical_currency_list/"),
			ESymbolSourceFormat::csv,
			ESymbolSourceFlags::None,
			[](SSymbolSource& obj) {
				obj.csv
				.column_types("string,string")
				.column_names("name,desc")
				.header_lines(1)
				.assume_header(true)
				.ignore_empty_lines(true); }
		)
	);
	AddSymbolUrls(instance,
		CQuantDataProvider::OpenExchange,
		SSymbolSource(U("api/currencies.json"),
			ESymbolSourceFormat::json,
			ESymbolSourceFlags::None,
			[](SSymbolSource&) {}
		)
	);
	return instance;
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// SYMBOLS //////////////////////////////////////////

constexpr TQuantDataSymbolInfo g_alphaVantageDigitalCurrencies[] =
{
	{"1ST","FirstBlood"},
	{"2GIVE","GiveCoin"},
	{"808","808Coin"},
	{"AC","AsiaCoin"},
	{"ACT","Achain"},
	{"ADA","Cardano"},
	{"ADK","Aidos-Kuneen"},
	{"ADL","Adelphoi"},
	{"ADT","adToken"},
	{"ADX","AdEx"},
	{"AE","Aeternity"},
	{"AEON","Aeon"},
	{"AGRS","IDNI-Agoras"},
	{"AMBER","AmberCoin"},
	{"AMP","Synereo"},
	{"ANC","Anoncoin"},
	{"ANS","NEO"},
	{"ANT","Aragon"},
	{"APX","APX-Ventures"},
	{"ARDR","Ardor"},
	{"ARK","Ark"},
	{"ATB","ATBCoin"},
	{"ATCC","ATC-Coin"},
	{"AUR","Auroracoin"},
	{"AVT","Aventus"},
	{"B3","B3Coin"},
	{"BAT","Basic-Attention-Token"},
	{"BAY","BitBay"},
	{"BCAP","BCAP"},
	{"BCC","BitConnect"},
	{"BCH","Bitcoin-Cash"},
	{"BCN","Bytecoin"},
	{"BCY","BitCrystals"},
	{"BDL","Bitdeal"},
	{"BELA","BelaCoin"},
	{"BET","DAO-Casino"},
	{"BIS","Bismuth"},
	{"BIT","First-Bitcoin"},
	{"BITB","BitBean"},
	{"BITBTC","BitBTC"},
	{"BITCNY","BitCNY"},
	{"BITEUR","BitEUR"},
	{"BITGBP","BitGBP"},
	{"BITOK","Bitok"},
	{"BITSILVER","BitSILVER"},
	{"BITUSD","BitUSD"},
	{"BLAS","BlakeStar"},
	{"BLK","Blackcoin"},
	{"BLN","Bolenum"},
	{"BLOCK","Blocknet"},
	{"BLOCKPAY","BlockPay"},
	{"BMC","Blackmoon-Crypto"},
	{"BNB","Binance-Coin"},
	{"BNT","Bancor-Network-Token"},
	{"BOST","BoostCoin"},
	{"BQ","bitqy"},
	{"BQX","Bitquence"},
	{"BTA","Bata"},
	{"BTC","Bitcoin"},
	{"BTCD","BitcoinDark"},
	{"BTM","Bitmark"},
	{"BTS","BitShares"},
	{"BTSR","BTSR"},
	{"BTX","Bitcore"},
	{"BURST","Burstcoin"},
	{"BUZZ","BuzzCoin"},
	{"BYC","Bytecent"},
	{"BYTOM","Bytom"},
	{"CANN","CannabisCoin"},
	{"CAT","BlockCAT"},
	{"CCRB","CryptoCarbon"},
	{"CDT","Coindash"},
	{"CFI","Cofound.it"},
	{"CHIPS","Chips"},
	{"CLAM","Clams"},
	{"CLOAK","CloakCoin"},
	{"CMP","Compcoin"},
	{"COSS","COSS"},
	{"COVAL","Circuits-Of-Value"},
	{"CRBIT","CreditBIT"},
	{"CREA","CreativeCoin"},
	{"CREDO","Credo"},
	{"CRW","Crown"},
	{"CTR","Centra"},
	{"CURE","CureCoin"},
	{"CVC","Civic"},
	{"DAR","Darcrus"},
	{"DASH","Dash"},
	{"DAY","Chronologic"},
	{"DCN","Dentacoin"},
	{"DCR","Decred"},
	{"DCT","DECENT"},
	{"DDF","Digital-Developers-Fund"},
	{"DENT","Dent"},
	{"DFS","DFSCoin"},
	{"DGB","DigiByte"},
	{"DGC","Digitalcoin"},
	{"DGD","DigixDAO"},
	{"DICE","Etheroll"},
	{"DNT","district0x"},
	{"DOGE","DogeCoin"},
	{"DOPE","DopeCoin"},
	{"DTB","Databits"},
	{"DYN","Dynamic"},
	{"EAC","EarthCoin"},
	{"EBST","eBoost"},
	{"EBTC","eBTC"},
	{"ECN","E-coin"},
	{"EDG","Edgeless"},
	{"ELIX","Elixir"},
	{"EMB","Embercoin"},
	{"EMC","Emercoin"},
	{"EMC2","Einsteinium"},
	{"EOS","EOS"},
	{"EOT","EOT-Token"},
	{"EQT","EquiTrader"},
	{"ETC","Ethereum-Classic"},
	{"ETH","Ethereum"},
	{"ETHD","Ethereum-Dark"},
	{"ETP","Metaverse-Entropy"},
	{"ETT","EncryptoTel"},
	{"EXP","Expanse"},
	{"FBC","Fibocoins"},
	{"FCT","Factom"},
	{"FID","BITFID"},
	{"FLDC","FoldingCoin"},
	{"FLO","FlorinCoin"},
	{"FLT","FlutterCoin"},
	{"FRST","FirstCoin"},
	{"FTC","Feathercoin"},
	{"FUN","FunFair"},
	{"GAM","Gambit"},
	{"GAME","GameCredits"},
	{"GAS","Gas"},
	{"GBG","Golos Gold"},
	{"GBYTE","Byteball"},
	{"GCR","GCRCoin"},
	{"GLD","GoldCoin"},
	{"GNO","Gnosis-Token"},
	{"GNT","Golem-Tokens"},
	{"GOLOS","Golos"},
	{"GRC","Gridcoin"},
	{"GRWI","Growers-International"},
	{"GUP","Guppy"},
	{"GXS","GXShares"},
	{"HBN","HoboNickels"},
	{"HEAT","HEAT"},
	{"HMQ","Humaniq"},
	{"HSR","Hshare"},
	{"HUSH","Hush"},
	{"HVN","Hive"},
	{"ICN","ICONOMI"},
	{"ICO","ICOCoin"},
	{"IFC","Infinitecoin"},
	{"IFT","investFeed"},
	{"INCNT","Incent"},
	{"IND","Indorse-Token"},
	{"INF","InfChain"},
	{"INPAY","InPay"},
	{"INXT","Internxt"},
	{"IOC","IOCoin"},
	{"ION","ION"},
	{"IOP","Internet-of-People"},
	{"IOT","IOTA"},
	{"IQT","Iquant-Chain"},
	{"IXC","iXcoin"},
	{"IXT","InsureX"},
	{"KEXCOIN","KexCoin"},
	{"KICK","KickCoin"},
	{"KIN","KIN"},
	{"KMD","Komodo"},
	{"KNC","Kyber-Network"},
	{"KORE","KoreCoin"},
	{"KRS","Krypstal"},
	{"LBC","LBRY-Credits"},
	{"LGD","Legends-Room"},
	{"LINDA","Linda"},
	{"LINK","ChainLink"},
	{"LKK","Lykke"},
	{"LMC","LoMoCoin"},
	{"LRC","Loopring"},
	{"LSK","Lisk"},
	{"LTC","Litecoin"},
	{"LUN","Lunyr"},
	{"MAGN","Magnetcoin"},
	{"MAID","MaidSafeCoin"},
	{"MANA","Decentraland"},
	{"MAX","Maxcoin"},
	{"MBRS","Embers"},
	{"MCAP","MCAP"},
	{"MCO","Monaco"},
	{"MDA","Moeda-Loyalty-Points"},
	{"MEC","Megacoin"},
	{"MEME","Memetic"},
	{"MGC","MergeCoin"},
	{"MGO","MobileGo"},
	{"MINEX","Minex"},
	{"MINT","Mintcoin"},
	{"MLN","Melon"},
	{"MNE","Minereum"},
	{"MONA","MonaCoin"},
	{"MRT","Miners-Reward-Token"},
	{"MSP","Mothership"},
	{"MTH","Monetha"},
	{"MUE","MonetaryUnit"},
	{"MUSIC","Musicoin"},
	{"MYB","MyBit-Token"},
	{"MYR","Myriadcoin"},
	{"MYST","Mysterium"},
	{"MZC","Mazacoin"},
	{"NAMO","Namocoin"},
	{"NAUT","NautilusCoin"},
	{"NAV","Nav-Coin"},
	{"NBT","NuBits"},
	{"NDAO","NeuroDAO"},
	{"NDC","NeverDie-Coin"},
	{"NEBL","Neblio"},
	{"NEOS","NeosCoin"},
	{"NET","Nimiq"},
	{"NLC2","NoLimitCoin"},
	{"NLG","Gulden"},
	{"NMC","Namecoin"},
	{"NMR","Numeraire"},
	{"NOBL","NobleCoin"},
	{"NOTE","DNotes"},
	{"NSR","NuShares"},
	{"NTO","Fujinto"},
	{"NVC","Novacoin"},
	{"NXC","Nexium"},
	{"NXS","Nexus"},
	{"NXT","Nxt"},
	{"OAX","openANX"},
	{"OBITS","Obits"},
	{"OCL","Oceanlab"},
	{"ODN","Obsidian"},
	{"OK","OKCash"},
	{"OMG","OmiseGo"},
	{"OMNI","Omni"},
	{"ONION","DeepOnion"},
	{"OPT","Opus"},
	{"PART","Particl"},
	{"PASC","PascalCoin"},
	{"PAY","TenX"},
	{"PBT","Primalbase-Token"},
	{"PING","CryptoPing"},
	{"PINK","Pinkcoin"},
	{"PIVX","PIVX"},
	{"PIX","Lampix"},
	{"PLBT","Polybius"},
	{"PLR","Pillar"},
	{"PLU","Pluton"},
	{"POE","Poet"},
	{"POSW","PoSW-Coin"},
	{"POT","PotCoin"},
	{"PPC","Peercoin"},
	{"PPT","Populous"},
	{"PPY","Peerplays"},
	{"PRO","Propy"},
	{"PST","Primas"},
	{"PTC","Pesetacoin"},
	{"PTOY","Patientory"},
	{"PURA","Pura"},
	{"QAU","Quantum"},
	{"QRK","Quark"},
	{"QRL","Quantum-Resistant-Ledger"},
	{"QTL","Quatloo"},
	{"QTUM","Qtum"},
	{"QWARK","Qwark"},
	{"RADS","Radium"},
	{"RAIN","Condensate"},
	{"RBIES","Rubies"},
	{"RBX","Ripto-Bux"},
	{"RBY","RubyCoin"},
	{"RDD","ReddCoin"},
	{"REC","Regalcoin"},
	{"RED","Redcoin"},
	{"REP","Augur"},
	{"RIC","Riecoin"},
	{"RISE","Rise"},
	{"RLC","RLC-Token"},
	{"RLT","RouletteToken"},
	{"ROUND","Round"},
	{"RRT","Recovery-Right-Tokens"},
	{"RUP","Rupee"},
	{"RVT","Rivetz"},
	{"SALT","Salt"},
	{"SAN","Santiment-Network-Token"},
	{"SBD","Steem-Dollars"},
	{"SC","Siacoin"},
	{"SDC","ShadowCash"},
	{"SEC","SafeExchangeCoin"},
	{"SEQ","Sequence"},
	{"SHIFT","SHIFT"},
	{"SIGMA","SIGMAcoin"},
	{"SIGT","Signatum"},
	{"SJCX","Storjcoin-X"},
	{"SKIN","SkinCoin"},
	{"SKY","Skycoin"},
	{"SLS","SaluS"},
	{"SMART","SmartCash"},
	{"SNC","SunContract"},
	{"SNGLS","SingularDTV"},
	{"SNM","SONM"},
	{"SNRG","Synergy"},
	{"SNT","Status-Network-Token"},
	{"SPR","SpreadCoin"},
	{"START","Startcoin"},
	{"STEEM","Steem"},
	{"STORJ","Storj"},
	{"STRAT","Stratis"},
	{"STRC","StarCredits"},
	{"STX","Stox"},
	{"SUB","Substratum"},
	{"SWT","Swarm-City"},
	{"SYS","SysCoin"},
	{"TAAS","Taas"},
	{"TCC","The-ChampCoin"},
	{"TFL","True-Flip"},
	{"TIME","Time"},
	{"TIX","Blocktix"},
	{"TKN","TokenCard"},
	{"TKR","Trackr"},
	{"TKS","Tokes"},
	{"TNT","Tierion"},
	{"TOA","ToaCoin"},
	{"TRC","Terracoin"},
	{"TRIG","Triggers"},
	{"TRST","Trustcoin"},
	{"TRX","Tronix"},
	{"UBQ","Ubiq"},
	{"ULA","Ulatech"},
	{"UNITY","SuperNET"},
	{"UNO","Unobtanium"},
	{"UNY","Unity-Ingot"},
	{"URO","Uro"},
	{"USDT","Tether"},
	{"VEN","VeChain"},
	{"VERI","Veritaseum"},
	{"VIA","Viacoin"},
	{"VIB","Viberate"},
	{"VIVO","VIVO"},
	{"VOISE","Voise"},
	{"VOX","Voxels"},
	{"VPN","VPNCoin"},
	{"VRC","Vericoin"},
	{"VRM","Verium"},
	{"VRS","Veros"},
	{"VSL","vSlice"},
	{"VTC","Vertcoin"},
	{"VTR","vTorrent"},
	{"WAVES","Waves"},
	{"WCT","Waves-Community"},
	{"WDC","WorldCoin"},
	{"WGO","WavesGo"},
	{"WGR","Wagerr"},
	{"WINGS","Wings"},
	{"WTC","Walton"},
	{"WTT","Giga-Watt-Token"},
	{"XAS","Asch"},
	{"XAUR","Xaurum"},
	{"XBC","Bitcoin-Plus"},
	{"XBY","XtraBYtes"},
	{"XCN","Cryptonite"},
	{"XCP","Counterparty"},
	{"XDN","DigitalNote"},
	{"XEL","Elastic"},
	{"XEM","NEM"},
	{"XID","Air"},
	{"XLM","Stellar"},
	{"XMR","Monero"},
	{"XMT","Metal"},
	{"XPM","Primecoin"},
	{"XPY","PayCoin"},
	{"XRB","RaiBlocks"},
	{"XRL","Rialto"},
	{"XRP","Ripples"},
	{"XSPEC","Spectrecoin"},
	{"XST","Stealthcoin"},
	{"XTZ","Tezos"},
	{"XVC","Vcash"},
	{"XVG","Verge"},
	{"XWC","WhiteCoin"},
	{"XZC","ZCoin"},
	{"XZR","ZrCoin"},
	{"YBC","YbCoin"},
	{"YOYOW","YOYOW"},
	{"ZCC","ZcCoin"},
	{"ZCL","Zclassic"},
	{"ZEC","Zcash"},
	{"ZEN","ZenCash"},
	{"ZET","Zetacoin"},
	{"ZRX","0x"},
};

constexpr TQuantDataSymbolInfo g_alphaVantagePhysicalCurrencies[] =
{
	{"AED","United Arab Emirates Dirham"},
	{"AFN","Afghan Afghani"},
	{"ALL","Albanian Lek"},
	{"AMD","Armenian Dram"},
	{"ANG","Netherlands Antillean Guilder"},
	{"AOA","Angolan Kwanza"},
	{"ARS","Argentine Peso"},
	{"AUD","Australian Dollar"},
	{"AWG","Aruban Florin"},
	{"AZN","Azerbaijani Manat"},
	{"BAM","Bosnia-Herzegovina Convertible Mark"},
	{"BBD","Barbadian Dollar"},
	{"BDT","Bangladeshi Taka"},
	{"BGN","Bulgarian Lev"},
	{"BHD","Bahraini Dinar"},
	{"BIF","Burundian Franc"},
	{"BITGOLD","BitGOLD"},
	{"BMD","Bermudan Dollar"},
	{"BND","Brunei Dollar"},
	{"BOB","Bolivian Boliviano"},
	{"BRL","Brazilian Real"},
	{"BSD","Bahamian Dollar"},
	{"BTN","Bhutanese Ngultrum"},
	{"BWP","Botswanan Pula"},
	{"BYR","Belarusian Ruble (pre-2016)"},
	{"BZD","Belize Dollar"},
	{"CAD","Canadian Dollar"},
	{"CDF","Congolese Franc"},
	{"CHF","Swiss Franc"},
	{"CLF","Chilean Unit of Account (UF)"},
	{"CLP","Chilean Peso"},
	{"CNY","Chinese Yuan"},
	{"COP","Colombian Peso"},
	{"CRC","Costa Rican Colon"},
	{"CUP","Cuban Peso"},
	{"CVE","Cape Verdean Escudo"},
	{"CZK","Czech Republic Koruna"},
	{"DJF","Djiboutian Franc"},
	{"DKK","Danish Krone"},
	{"DOP","Dominican Peso"},
	{"DZD","Algerian Dinar"},
	{"EEK","Estonian Kroon"},
	{"EGP","Egyptian Pound"},
	{"ERN","Eritrean Nakfa"},
	{"ETB","Ethiopian Birr"},
	{"EUR","Euro"},
	{"FJD","Fijian Dollar"},
	{"FKP","Falkland Islands Pound"},
	{"GBP","British Pound Sterling"},
	{"GEL","Georgian Lari"},
	{"GHS","Ghanaian Cedi"},
	{"GIP","Gibraltar Pound"},
	{"GMD","Gambian Dalasi"},
	{"GNF","Guinean Franc"},
	{"GTQ","Guatemalan Quetzal"},
	{"GYD","Guyanaese Dollar"},
	{"HKD","Hong Kong Dollar"},
	{"HNL","Honduran Lempira"},
	{"HRK","Croatian Kuna"},
	{"HTG","Haitian Gourde"},
	{"HUF","Hungarian Forint"},
	{"IDR","Indonesian Rupiah"},
	{"ILS","Israeli New Sheqel"},
	{"INR","Indian Rupee"},
	{"IQD","Iraqi Dinar"},
	{"IRR","Iranian Rial"},
	{"ISK","Icelandic Krona"},
	{"JEP","Jersey Pound"},
	{"JMD","Jamaican Dollar"},
	{"JOD","Jordanian Dinar"},
	{"JPY","Japanese Yen"},
	{"KES","Kenyan Shilling"},
	{"KGS","Kyrgystani Som"},
	{"KHR","Cambodian Riel"},
	{"KMF","Comorian Franc"},
	{"KPW","North Korean Won"},
	{"KRW","South Korean Won"},
	{"KWD","Kuwaiti Dinar"},
	{"KYD","Cayman Islands Dollar"},
	{"KZT","Kazakhstani Tenge"},
	{"LAK","Laotian Kip"},
	{"LBP","Lebanese Pound"},
	{"LKR","Sri Lankan Rupee"},
	{"LRD","Liberian Dollar"},
	{"LSL","Lesotho Loti"},
	{"LTL","Lithuanian Litas"},
	{"LVL","Latvian Lats"},
	{"LYD","Libyan Dinar"},
	{"MAD","Moroccan Dirham"},
	{"MDL","Moldovan Leu"},
	{"MGA","Malagasy Ariary"},
	{"MKD","Macedonian Denar"},
	{"MMK","Myanma Kyat"},
	{"MNT","Mongolian Tugrik"},
	{"MOP","Macanese Pataca"},
	{"MRO","Mauritanian Ouguiya"},
	{"MTL","Maltese Lira"},
	{"MUR","Mauritian Rupee"},
	{"MVR","Maldivian Rufiyaa"},
	{"MWK","Malawian Kwacha"},
	{"MXN","Mexican Peso"},
	{"MYRf","Malaysian Ringgit"},
	{"MZN","Mozambican Metical"},
	{"NAD","Namibian Dollar"},
	{"NGN","Nigerian Naira"},
	{"NIO","Nicaraguan Cordoba"},
	{"NOK","Norwegian Krone"},
	{"NPR","Nepalese Rupee"},
	{"NZD","New Zealand Dollar"},
	{"OMR","Omani Rial"},
	{"PAB","Panamanian Balboa"},
	{"PEN","Peruvian Nuevo Sol"},
	{"PGK","Papua New Guinean Kina"},
	{"PHP","Philippine Peso"},
	{"PKR","Pakistani Rupee"},
	{"PLN","Polish Zloty"},
	{"PYG","Paraguayan Guarani"},
	{"QAR","Qatari Rial"},
	{"RON","Romanian Leu"},
	{"RSD","Serbian Dinar"},
	{"RUB","Russian Ruble"},
	{"RUR","Old Russian Ruble"},
	{"RWF","Rwandan Franc"},
	{"SAR","Saudi Riyal"},
	{"SBDf","Solomon Islands Dollar"},
	{"SCR","Seychellois Rupee"},
	{"SDG","Sudanese Pound"},
	{"SEK","Swedish Krona"},
	{"SGD","Singapore Dollar"},
	{"SHP","Saint Helena Pound"},
	{"SLL","Sierra Leonean Leone"},
	{"SOS","Somali Shilling"},
	{"SRD","Surinamese Dollar"},
	{"STD","Sao Tome and Principe Dobra"},
	{"SVC","Salvadoran Colon"},
	{"SYP","Syrian Pound"},
	{"SZL","Swazi Lilangeni"},
	{"THB","Thai Baht"},
	{"TJS","Tajikistani Somoni"},
	{"TMT","Turkmenistani Manat"},
	{"TND","Tunisian Dinar"},
	{"TOP","Tongan Pa'anga"},
	{"TRY","Turkish Lira"},
	{"TTD","Trinidad and Tobago Dollar"},
	{"TWD","New Taiwan Dollar"},
	{"TZS","Tanzanian Shilling"},
	{"UAH","Ukrainian Hryvnia"},
	{"UGX","Ugandan Shilling"},
	{"USD","United States Dollar"},
	{"USDE","USDe"},
	{"UYU","Uruguayan Peso"},
	{"UZS","Uzbekistan Som"},
	{"VEF","Venezuelan Bolivar Fuerte"},
	{"VND","Vietnamese Dong"},
	{"VUV","Vanuatu Vatu"},
	{"WST","Samoan Tala"},
	{"XAF","CFA Franc BEAC"},
	{"XAG","Silver Ounce"},
	{"XAU","Gold Ounce"},
	{"XCD","East Caribbean Dollar"},
	{"XDR","Special Drawing Rights"},
	{"XOF","CFA Franc BCEAO"},
	{"XPF","CFP Franc"},
	{"YER","Yemeni Rial"},
	{"ZAR","South African Rand"},
	{"ZMK","Zambian Kwacha (pre-2013)"},
	{"ZMW","Zambian Kwacha"},
	{"ZWL","Zimbabwean Dollar"},
};

constexpr TQuantDataSymbolInfo g_openExchangeSymbols[] =
{
	{"AED", "United Arab Emirates Dirham"},
	{"AFN", "Afghan Afghani"},
	{"ALL", "Albanian Lek"},
	{"AMD", "Armenian Dram"},
	{"ANG", "Netherlands Antillean Guilder"},
	{"AOA", "Angolan Kwanza"},
	{"ARS", "Argentine Peso"},
	{"AUD", "Australian Dollar"},
	{"AWG", "Aruban Florin"},
	{"AZN", "Azerbaijani Manat"},
	{"BAM", "Bosnia-Herzegovina Convertible Mark"},
	{"BBD", "Barbadian Dollar"},
	{"BDT", "Bangladeshi Taka"},
	{"BGN", "Bulgarian Lev"},
	{"BHD", "Bahraini Dinar"},
	{"BIF", "Burundian Franc"},
	{"BMD", "Bermudan Dollar"},
	{"BND", "Brunei Dollar"},
	{"BOB", "Bolivian Boliviano"},
	{"BRL", "Brazilian Real"},
	{"BSD", "Bahamian Dollar"},
	{"BTC", "Bitcoin"},
	{"BTN", "Bhutanese Ngultrum"},
	{"BWP", "Botswanan Pula"},
	{"BYN", "Belarusian Ruble"},
	{"BZD", "Belize Dollar"},
	{"CAD", "Canadian Dollar"},
	{"CDF", "Congolese Franc"},
	{"CHF", "Swiss Franc"},
	{"CLF", "Chilean Unit of Account (UF)"},
	{"CLP", "Chilean Peso"},
	{"CNH", "Chinese Yuan (Offshore)"},
	{"CNY", "Chinese Yuan"},
	{"COP", "Colombian Peso"},
	{"CRC", "Costa Rican Colón"},
	{"CUC", "Cuban Convertible Peso"},
	{"CUP", "Cuban Peso"},
	{"CVE", "Cape Verdean Escudo"},
	{"CZK", "Czech Republic Koruna"},
	{"DJF", "Djiboutian Franc"},
	{"DKK", "Danish Krone"},
	{"DOP", "Dominican Peso"},
	{"DZD", "Algerian Dinar"},
	{"EGP", "Egyptian Pound"},
	{"ERN", "Eritrean Nakfa"},
	{"ETB", "Ethiopian Birr"},
	{"EUR", "Euro"},
	{"FJD", "Fijian Dollar"},
	{"FKP", "Falkland Islands Pound"},
	{"GBP", "British Pound Sterling"},
	{"GEL", "Georgian Lari"},
	{"GGP", "Guernsey Pound"},
	{"GHS", "Ghanaian Cedi"},
	{"GIP", "Gibraltar Pound"},
	{"GMD", "Gambian Dalasi"},
	{"GNF", "Guinean Franc"},
	{"GTQ", "Guatemalan Quetzal"},
	{"GYD", "Guyanaese Dollar"},
	{"HKD", "Hong Kong Dollar"},
	{"HNL", "Honduran Lempira"},
	{"HRK", "Croatian Kuna"},
	{"HTG", "Haitian Gourde"},
	{"HUF", "Hungarian Forint"},
	{"IDR", "Indonesian Rupiah"},
	{"ILS", "Israeli New Sheqel"},
	{"IMP", "Manx pound"},
	{"INR", "Indian Rupee"},
	{"IQD", "Iraqi Dinar"},
	{"IRR", "Iranian Rial"},
	{"ISK", "Icelandic Króna"},
	{"JEP", "Jersey Pound"},
	{"JMD", "Jamaican Dollar"},
	{"JOD", "Jordanian Dinar"},
	{"JPY", "Japanese Yen"},
	{"KES", "Kenyan Shilling"},
	{"KGS", "Kyrgystani Som"},
	{"KHR", "Cambodian Riel"},
	{"KMF", "Comorian Franc"},
	{"KPW", "North Korean Won"},
	{"KRW", "South Korean Won"},
	{"KWD", "Kuwaiti Dinar"},
	{"KYD", "Cayman Islands Dollar"},
	{"KZT", "Kazakhstani Tenge"},
	{"LAK", "Laotian Kip"},
	{"LBP", "Lebanese Pound"},
	{"LKR", "Sri Lankan Rupee"},
	{"LRD", "Liberian Dollar"},
	{"LSL", "Lesotho Loti"},
	{"LYD", "Libyan Dinar"},
	{"MAD", "Moroccan Dirham"},
	{"MDL", "Moldovan Leu"},
	{"MGA", "Malagasy Ariary"},
	{"MKD", "Macedonian Denar"},
	{"MMK", "Myanma Kyat"},
	{"MNT", "Mongolian Tugrik"},
	{"MOP", "Macanese Pataca"},
	{"MRO", "Mauritanian Ouguiya"},
	{"MUR", "Mauritian Rupee"},
	{"MVR", "Maldivian Rufiyaa"},
	{"MWK", "Malawian Kwacha"},
	{"MXN", "Mexican Peso"},
	{"MYR", "Malaysian Ringgit"},
	{"MZN", "Mozambican Metical"},
	{"NAD", "Namibian Dollar"},
	{"NGN", "Nigerian Naira"},
	{"NIO", "Nicaraguan Córdoba"},
	{"NOK", "Norwegian Krone"},
	{"NPR", "Nepalese Rupee"},
	{"NZD", "New Zealand Dollar"},
	{"OMR", "Omani Rial"},
	{"PAB", "Panamanian Balboa"},
	{"PEN", "Peruvian Nuevo Sol"},
	{"PGK", "Papua New Guinean Kina"},
	{"PHP", "Philippine Peso"},
	{"PKR", "Pakistani Rupee"},
	{"PLN", "Polish Zloty"},
	{"PYG", "Paraguayan Guarani"},
	{"QAR", "Qatari Rial"},
	{"RON", "Romanian Leu"},
	{"RSD", "Serbian Dinar"},
	{"RUB", "Russian Ruble"},
	{"RWF", "Rwandan Franc"},
	{"SAR", "Saudi Riyal"},
	{"SBD", "Solomon Islands Dollar"},
	{"SCR", "Seychellois Rupee"},
	{"SDG", "Sudanese Pound"},
	{"SEK", "Swedish Krona"},
	{"SGD", "Singapore Dollar"},
	{"SHP", "Saint Helena Pound"},
	{"SLL", "Sierra Leonean Leone"},
	{"SOS", "Somali Shilling"},
	{"SRD", "Surinamese Dollar"},
	{"SSP", "South Sudanese Pound"},
	{"STD", "São Tomé and Príncipe Dobra"},
	{"SVC", "Salvadoran Colón"},
	{"SYP", "Syrian Pound"},
	{"SZL", "Swazi Lilangeni"},
	{"THB", "Thai Baht"},
	{"TJS", "Tajikistani Somoni"},
	{"TMT", "Turkmenistani Manat"},
	{"TND", "Tunisian Dinar"},
	{"TOP", "Tongan Pa'anga"},
	{"TRY", "Turkish Lira"},
	{"TTD", "Trinidad and Tobago Dollar"},
	{"TWD", "New Taiwan Dollar"},
	{"TZS", "Tanzanian Shilling"},
	{"UAH", "Ukrainian Hryvnia"},
	{"UGX", "Ugandan Shilling"},
	{"USD", "United States Dollar"},
	{"UYU", "Uruguayan Peso"},
	{"UZS", "Uzbekistan Som"},
	{"VEF", "Venezuelan Bolívar Fuerte"},
	{"VND", "Vietnamese Dong"},
	{"VUV", "Vanuatu Vatu"},
	{"WST", "Samoan Tala"},
	{"XAF", "CFA Franc BEAC"},
	{"XAG", "Silver Ounce"},
	{"XAU", "Gold Ounce"},
	{"XCD", "East Caribbean Dollar"},
	{"XDR", "Special Drawing Rights"},
	{"XOF", "CFA Franc BCEAO"},
	{"XPD", "Palladium Ounce"},
	{"XPF", "CFP Franc"},
	{"XPT", "Platinum Ounce"},
	{"YER", "Yemeni Rial"},
	{"ZAR", "South African Rand"},
	{"ZMW", "Zambian Kwacha"},
	{"ZWL", "Zimbabwean Dollar"},
};

constexpr TQuantDataSymbolInfo g_trueFxSymbols[] =
{
	{"EUR/USD", ""},
	{"USD/JPY", ""},
	{"GBP/USD", ""},
	{"EUR/GBP", ""},
	{"CAD/CHF", ""},
	{"CAD/JPY", ""},
	{"CHF/JPY", ""},
	{"EUR/AUD", ""},
	{"USD/CHF", ""},
	{"EUR/JPY", ""},
	{"EUR/CHF", ""},
	{"USD/CAD", ""},
	{"AUD/USD", ""},
	{"GBP/JPY", ""},
	{"AUD/CAD", ""},
	{"AUD/CHF", ""},
	{"AUD/JPY", ""},
	{"AUD/NZD", ""},
	{"EUR/CAD", ""},
	{"EUR/NOK", ""},
	{"EUR/NZD", ""},
	{"GBP/CAD", ""},
	{"GBP/CHF", ""},
	{"NZD/JPY", ""},
	{"NZD/USD", ""},
	{"USD/NOK", ""},
	{"USD/SEK", ""},
};

using TSymbols             = std::vector<TQuantDataSymbolInfo>;
using TSymbolsList         = std::vector<TSymbols>;
using TProviderSymbolsList = std::array<TSymbolsList, CQuantDataProvider::count()>;

template <class Type, size_t Size>
inline void AddSymbols(TProviderSymbolsList& instance, CQuantDataProvider provider, const Type(&symbolArray)[Size])
{
	TSymbolsList& symbolsList = instance[provider.ordinal()];
	symbolsList.resize(symbolsList.size() + 1);
	TSymbols& symbols = symbolsList.back();
	symbols.resize(Size);
	std::copy(symbolArray, symbolArray + Size, symbols.begin());
}

inline TProviderSymbolsList BuildProviderSymbolsList()
{
	TProviderSymbolsList instance;
	AddSymbols(instance, CQuantDataProvider::AlphaVantage, g_alphaVantageDigitalCurrencies);
	AddSymbols(instance, CQuantDataProvider::AlphaVantage, g_alphaVantagePhysicalCurrencies);
	AddSymbols(instance, CQuantDataProvider::OpenExchange, g_openExchangeSymbols);
	AddSymbols(instance, CQuantDataProvider::TrueFx      , g_trueFxSymbols);
	return instance;
}


} // namespace internal
} // namespace quantdata
