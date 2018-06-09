[@bs.val] external uri : string = "REACT_APP_GRAPHQL_URL";

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();
let httpLink = ApolloLinks.createHttpLink(~uri, ());

let instance =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());
