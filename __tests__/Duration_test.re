open Jest;

describe("Expect", () => {
  open Expect;

  test("returns time with 0:s", () =>
    expect(Duration.parse(50000.0)) |> toEqual("0:50")
  );

  test("returns when seconds are super close to 60", () =>
    expect(Duration.parse(59999.0)) |> toEqual("0:59")
  );

  test("returns when seconds are exactly 60", () =>
    expect(Duration.parse(60000.0)) |> toEqual("1:00")
  );

  test("returns time with min:s", () =>
    expect(Duration.parse(500000.0)) |> toEqual("8:20")
  );

  test("returns when minutes are super close to 60", () =>
    expect(Duration.parse(3599999.0)) |> toEqual("59:59")
  );

  test("returns when minutes are exactly 60", () =>
    expect(Duration.parse(3600000.0)) |> toEqual("1:00:00")
  );

  test("returns time with h:min:s", () =>
    expect(Duration.parse(5000000.0)) |> toEqual("1:23:19")
  );
});
