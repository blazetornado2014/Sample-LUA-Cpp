-- Different ways of declaring in LUA

-- PlayerTitle = "Squire"
-- PlayerName = "Ciaran"
-- PlayerFamily = "Wirral"
-- PlayerLevel = "20"

-- player = {}
-- player["Title"] = "Squire"
-- player["Name"] = "Ciaran"
-- player["Family"] = "Wirral"
-- player["Level"] = "20"

players = {}
players[0] = { Title = "Squire",
			Name = "Ciaran",
			Family = "Wirral",
			Level = "20"}

players[1] = { Title = "Squires",
			Name = "Ciarans",
			Family = "Wirrals",
			Level = "200"}

function AddVar(a, b)
	print("[LUA] AddVar("..a..","..b..") called \n");
	return a * b;
end

function GetPlayer(n)
	return players[n]
end

function DoSomething(a, b)
	print("[LUA] DoSomething("..a..","..b..") called \n");

	c = HostFunction(a + 10, b + 42)
	return c;
end