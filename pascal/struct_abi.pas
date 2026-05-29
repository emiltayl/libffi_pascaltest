library struct_abi;

{$mode delphi}
{$C+}

type
  TFourInt64 = record
    a: QWord;
    b: QWord;
    c: QWord;
    d: QWord;
  end;

  TOneInteger = record
    value: Integer;
  end;

  TFourByteRecord = packed record
    a: AnsiChar;
    b: AnsiChar;
    c: AnsiChar;
    d: AnsiChar;
  end;

  TFiveByteRecord = packed record
    a: AnsiChar;
    b: AnsiChar;
    c: AnsiChar;
    d: AnsiChar;
    e: AnsiChar;
  end;

  TCdeclCallback = function(value: TFourInt64): TFourInt64; cdecl;
  TPascalCallback = function(value: TFourInt64): TFourInt64; pascal;
  TRegisterCallback = function(value: TFourInt64): TFourInt64; register;
  TTwoRegisterCallback = function(a: Integer; value: TFourInt64): TFourInt64; register;
  TThreeRegisterCallback = function(a: Integer; b: Integer; value: TFourInt64): TFourInt64; register;
  TFourRegisterCallback = function(a: Integer; b: Integer; c: Integer; value: TFourInt64): TFourInt64; register;
  TIntStructIntPascalCallback = function(a: Integer; b: TFourInt64; c: Integer): TFourInt64; pascal;
  TIntStructIntRegisterCallback = function(a: Integer; b: TFourInt64; c: Integer): TFourInt64; register;
  TOneIntegerPascalCallback = function(value: TOneInteger): TOneInteger; pascal;
  TOneIntegerRegisterCallback = function(value: TOneInteger): TOneInteger; register;
  TTwoIntOneIntegerPascalCallback = function(a: Integer; b: Integer; c: TOneInteger): TOneInteger; pascal;
  TTwoIntOneIntegerRegisterCallback = function(a: Integer; b: Integer; c: TOneInteger): TOneInteger; register;
  TIntOneIntegerIntPascalCallback = function(a: Integer; b: TOneInteger; c: Integer): TOneInteger; pascal;
  TIntOneIntegerIntRegisterCallback = function(a: Integer; b: TOneInteger; c: Integer): TOneInteger; register;
  TFourBytePascalCallback = function(value: TFourByteRecord): TFourByteRecord; pascal;
  TFourByteRegisterCallback = function(value: TFourByteRecord): TFourByteRecord; register;
  TFiveBytePascalCallback = function(value: TFiveByteRecord): TFiveByteRecord; pascal;
  TFiveByteRegisterCallback = function(value: TFiveByteRecord): TFiveByteRecord; register;
  TIntPascalCallback = function(value: Integer): Integer; pascal;
  TFourIntRegisterCallback = function(a: Integer; b: Integer; c: Integer; d: Integer): Integer; register;
  TMixedAlignmentPascalCallback = function(a: ShortInt; b: SmallInt; c: LongInt; d: Int64; e: Single; f: Double): LongInt; pascal;
  TMixedAlignmentRegisterCallback = function(a: ShortInt; b: SmallInt; c: LongInt; d: Int64; e: Single; f: Double): LongInt; register;

function MakeTestStruct: TFourInt64;
begin
  Result.a := QWord($5555555555555555);
  Result.b := QWord($AAAAAAAAAAAAAAAA);
  Result.c := QWord($6666666666666666);
  Result.d := QWord($9999999999999999);
end;

procedure AssertSameStruct(expected: TFourInt64; actual: TFourInt64);
begin
  Assert(expected.a = actual.a);
  Assert(expected.b = actual.b);
  Assert(expected.c = actual.c);
  Assert(expected.d = actual.d);
end;

function MakeOneIntegerStruct: TOneInteger;
begin
  Result.value := Integer($12345678);
end;

procedure AssertSameOneIntegerStruct(expected: TOneInteger; actual: TOneInteger);
begin
  Assert(expected.value = actual.value);
end;

function MakeFourByteRecord: TFourByteRecord;
begin
  Assert(SizeOf(TFourByteRecord) = 4);
  Result.a := '0';
  Result.b := '1';
  Result.c := '2';
  Result.d := '3';
end;

procedure AssertSameFourByteRecord(expected: TFourByteRecord; actual: TFourByteRecord);
begin
  Assert(expected.a = actual.a);
  Assert(expected.b = actual.b);
  Assert(expected.c = actual.c);
  Assert(expected.d = actual.d);
end;

function MakeFiveByteRecord: TFiveByteRecord;
begin
  Assert(SizeOf(TFiveByteRecord) = 5);
  Result.a := '0';
  Result.b := '1';
  Result.c := '2';
  Result.d := '3';
  Result.e := '4';
end;

procedure AssertSameFiveByteRecord(expected: TFiveByteRecord; actual: TFiveByteRecord);
begin
  Assert(expected.a = actual.a);
  Assert(expected.b = actual.b);
  Assert(expected.c = actual.c);
  Assert(expected.d = actual.d);
  Assert(expected.e = actual.e);
end;

function VerifyMixedAlignmentValues(a: ShortInt; b: SmallInt; c: LongInt; d: Int64; e: Single; f: Double): LongInt;
begin
  Assert(a = ShortInt($12));
  Assert(b = SmallInt($3456));
  Assert(c = LongInt($12345678));
  Assert(d = Int64($1122334455667788));
  Assert(e = Single(16.25));
  Assert(f = Double(1024.5));
  Result := LongInt($13572468);
end;

function return_struct_cdecl: TFourInt64; cdecl;
begin
  Result := MakeTestStruct;
end;

function return_struct_pascal: TFourInt64; pascal;
begin
  Result := MakeTestStruct;
end;

function return_struct_register: TFourInt64; register;
begin
  Result := MakeTestStruct;
end;

procedure verify_struct_cdecl(value: TFourInt64); cdecl;
var
  expected: TFourInt64;
begin
  expected := MakeTestStruct;
  AssertSameStruct(value, expected);
end;

procedure verify_struct_pascal(value: TFourInt64); pascal;
var
  expected: TFourInt64;
begin
  expected := MakeTestStruct;
  AssertSameStruct(value, expected);
end;

procedure verify_struct_register(value: TFourInt64); register;
var
  expected: TFourInt64;
begin
  expected := MakeTestStruct;
  AssertSameStruct(value, expected);
end;

function identity_cdecl(value: TFourInt64): TFourInt64; cdecl;
begin
  Result := value;
end;

function identity_pascal(value: TFourInt64): TFourInt64; pascal;
begin
  Result := value;
end;

function identity_register(value: TFourInt64): TFourInt64; register;
begin
  Result := value;
end;

procedure verify_callback_cdecl(callback: TCdeclCallback); cdecl;
var
  input: TFourInt64;
  output: TFourInt64;
begin
  Assert(Assigned(callback));
  input := MakeTestStruct;
  output := callback(input);
  AssertSameStruct(input, output);
end;

procedure verify_callback_pascal(callback: TPascalCallback); cdecl;
var
  input: TFourInt64;
  output: TFourInt64;
begin
  Assert(Assigned(callback));
  input := MakeTestStruct;
  output := callback(input);
  AssertSameStruct(input, output);
end;

procedure verify_callback_register(callback: TRegisterCallback); cdecl;
var
  input: TFourInt64;
  output: TFourInt64;
begin
  Assert(Assigned(callback));
  input := MakeTestStruct;
  output := callback(input);
  AssertSameStruct(input, output);
end;

function register_two_args_return_struct(a: Integer; b: TFourInt64): TFourInt64; register;
begin
  Assert(a = 0);
  Result := b;
end;

function register_three_args_return_struct(a: Integer; b: Integer; c: TFourInt64): TFourInt64; register;
begin
  Assert(a = 0);
  Assert(b = 1);
  Result := c;
end;

function register_four_args_return_struct(a: Integer; b: Integer; c: Integer; d: TFourInt64): TFourInt64; register;
begin
  Assert(a = 0);
  Assert(b = 1);
  Assert(c = 2);
  Result := d;
end;

procedure verify_two_args_callback_register(callback: TTwoRegisterCallback); cdecl;
var
  input: TFourInt64;
  output: TFourInt64;
begin
  Assert(Assigned(callback));
  input := MakeTestStruct;
  output := callback(0, input);
  AssertSameStruct(input, output);
end;

procedure verify_three_args_callback_register(callback: TThreeRegisterCallback); cdecl;
var
  input: TFourInt64;
  output: TFourInt64;
begin
  Assert(Assigned(callback));
  input := MakeTestStruct;
  output := callback(0, 1, input);
  AssertSameStruct(input, output);
end;

procedure verify_four_args_callback_register(callback: TFourRegisterCallback); cdecl;
var
  input: TFourInt64;
  output: TFourInt64;
begin
  Assert(Assigned(callback));
  input := MakeTestStruct;
  output := callback(0, 1, 2, input);
  AssertSameStruct(input, output);
end;

function verify_int_struct_int_pascal(a: Integer; b: TFourInt64; c: Integer): TFourInt64; pascal;
var
  expected: TFourInt64;
begin
  Assert(a = 0);
  Assert(c = 1);
  expected := MakeTestStruct;
  AssertSameStruct(b, expected);

  Result := b;
end;

function verify_int_struct_int_register(a: Integer; b: TFourInt64; c: Integer): TFourInt64; register;
var
  expected: TFourInt64;
begin
  Assert(a = 0);
  Assert(c = 1);
  expected := MakeTestStruct;
  AssertSameStruct(b, expected);

  Result := b;
end;

procedure verify_int_struct_int_callback_pascal(callback: TIntStructIntPascalCallback); cdecl;
var
  input: TFourInt64;
  output: TFourInt64;
begin
  Assert(Assigned(callback));
  input := MakeTestStruct;
  output := callback(0, input, 1);
  AssertSameStruct(input, output);
end;

procedure verify_int_struct_int_callback_register(callback: TIntStructIntRegisterCallback); cdecl;
var
  input: TFourInt64;
  output: TFourInt64;
begin
  Assert(Assigned(callback));
  input := MakeTestStruct;
  output := callback(0, input, 1);
  AssertSameStruct(input, output);
end;

function return_one_integer_struct_pascal: TOneInteger; pascal;
begin
  Result := MakeOneIntegerStruct;
end;

function return_one_integer_struct_register: TOneInteger; register;
begin
  Result := MakeOneIntegerStruct;
end;

procedure verify_one_integer_struct_pascal(value: TOneInteger); pascal;
var
  expected: TOneInteger;
begin
  expected := MakeOneIntegerStruct;
  AssertSameOneIntegerStruct(value, expected);
end;

procedure verify_one_integer_struct_register(value: TOneInteger); register;
var
  expected: TOneInteger;
begin
  expected := MakeOneIntegerStruct;
  AssertSameOneIntegerStruct(value, expected);
end;

procedure verify_two_int_one_integer_struct_pascal(a: Integer; b: Integer; c: TOneInteger); pascal;
var
  expected: TOneInteger;
begin
  Assert(a = 0);
  Assert(b = 1);
  expected := MakeOneIntegerStruct;
  AssertSameOneIntegerStruct(c, expected);
end;

procedure verify_two_int_one_integer_struct_register(a: Integer; b: Integer; c: TOneInteger); register;
var
  expected: TOneInteger;
begin
  Assert(a = 0);
  Assert(b = 1);
  expected := MakeOneIntegerStruct;
  AssertSameOneIntegerStruct(c, expected);
end;

function return_two_int_one_integer_struct_pascal(a: Integer; b: Integer; c: TOneInteger): TOneInteger; pascal;
begin
  Assert(a = 0);
  Assert(b = 1);
  Result := c;
end;

function return_two_int_one_integer_struct_register(a: Integer; b: Integer; c: TOneInteger): TOneInteger; register;
begin
  Assert(a = 0);
  Assert(b = 1);
  Result := c;
end;

procedure verify_int_one_integer_int_pascal(a: Integer; b: TOneInteger; c: Integer); pascal;
var
  expected: TOneInteger;
begin
  Assert(a = 0);
  Assert(c = 1);
  expected := MakeOneIntegerStruct;
  AssertSameOneIntegerStruct(b, expected);
end;

procedure verify_int_one_integer_int_register(a: Integer; b: TOneInteger; c: Integer); register;
var
  expected: TOneInteger;
begin
  Assert(a = 0);
  Assert(c = 1);
  expected := MakeOneIntegerStruct;
  AssertSameOneIntegerStruct(b, expected);
end;

function return_int_one_integer_int_pascal(a: Integer; b: TOneInteger; c: Integer): TOneInteger; pascal;
begin
  Assert(a = 0);
  Assert(c = 1);
  Result := b;
end;

function return_int_one_integer_int_register(a: Integer; b: TOneInteger; c: Integer): TOneInteger; register;
begin
  Assert(a = 0);
  Assert(c = 1);
  Result := b;
end;

procedure verify_one_integer_callback_pascal(callback: TOneIntegerPascalCallback); cdecl;
var
  input: TOneInteger;
  output: TOneInteger;
begin
  Assert(Assigned(callback));
  input := MakeOneIntegerStruct;
  output := callback(input);
  AssertSameOneIntegerStruct(input, output);
end;

procedure verify_one_integer_callback_register(callback: TOneIntegerRegisterCallback); cdecl;
var
  input: TOneInteger;
  output: TOneInteger;
begin
  Assert(Assigned(callback));
  input := MakeOneIntegerStruct;
  output := callback(input);
  AssertSameOneIntegerStruct(input, output);
end;

procedure verify_two_int_one_integer_callback_pascal(callback: TTwoIntOneIntegerPascalCallback); cdecl;
var
  input: TOneInteger;
  output: TOneInteger;
begin
  Assert(Assigned(callback));
  input := MakeOneIntegerStruct;
  output := callback(0, 1, input);
  AssertSameOneIntegerStruct(input, output);
end;

procedure verify_two_int_one_integer_callback_register(callback: TTwoIntOneIntegerRegisterCallback); cdecl;
var
  input: TOneInteger;
  output: TOneInteger;
begin
  Assert(Assigned(callback));
  input := MakeOneIntegerStruct;
  output := callback(0, 1, input);
  AssertSameOneIntegerStruct(input, output);
end;

procedure verify_int_one_integer_int_callback_pascal(callback: TIntOneIntegerIntPascalCallback); cdecl;
var
  input: TOneInteger;
  output: TOneInteger;
begin
  Assert(Assigned(callback));
  input := MakeOneIntegerStruct;
  output := callback(0, input, 1);
  AssertSameOneIntegerStruct(input, output);
end;

procedure verify_int_one_integer_int_callback_register(callback: TIntOneIntegerIntRegisterCallback); cdecl;
var
  input: TOneInteger;
  output: TOneInteger;
begin
  Assert(Assigned(callback));
  input := MakeOneIntegerStruct;
  output := callback(0, input, 1);
  AssertSameOneIntegerStruct(input, output);
end;

function identity_four_byte_struct_pascal(value: TFourByteRecord): TFourByteRecord; pascal;
var
  expected: TFourByteRecord;
begin
  expected := MakeFourByteRecord;
  AssertSameFourByteRecord(expected, value);
  Result := value;
end;

function identity_four_byte_struct_register(value: TFourByteRecord): TFourByteRecord; register;
var
  expected: TFourByteRecord;
begin
  expected := MakeFourByteRecord;
  AssertSameFourByteRecord(expected, value);
  Result := value;
end;

function identity_five_byte_struct_pascal(value: TFiveByteRecord): TFiveByteRecord; pascal;
var
  expected: TFiveByteRecord;
begin
  expected := MakeFiveByteRecord;
  AssertSameFiveByteRecord(expected, value);
  Result := value;
end;

function identity_five_byte_struct_register(value: TFiveByteRecord): TFiveByteRecord; register;
var
  expected: TFiveByteRecord;
begin
  expected := MakeFiveByteRecord;
  AssertSameFiveByteRecord(expected, value);
  Result := value;
end;

procedure verify_four_byte_callback_pascal(callback: TFourBytePascalCallback); cdecl;
var
  input: TFourByteRecord;
  output: TFourByteRecord;
begin
  Assert(Assigned(callback));
  input := MakeFourByteRecord;
  output := callback(input);
  AssertSameFourByteRecord(input, output);
end;

procedure verify_four_byte_callback_register(callback: TFourByteRegisterCallback); cdecl;
var
  input: TFourByteRecord;
  output: TFourByteRecord;
begin
  Assert(Assigned(callback));
  input := MakeFourByteRecord;
  output := callback(input);
  AssertSameFourByteRecord(input, output);
end;

procedure verify_five_byte_callback_pascal(callback: TFiveBytePascalCallback); cdecl;
var
  input: TFiveByteRecord;
  output: TFiveByteRecord;
begin
  Assert(Assigned(callback));
  input := MakeFiveByteRecord;
  output := callback(input);
  AssertSameFiveByteRecord(input, output);
end;

procedure verify_five_byte_callback_register(callback: TFiveByteRegisterCallback); cdecl;
var
  input: TFiveByteRecord;
  output: TFiveByteRecord;
begin
  Assert(Assigned(callback));
  input := MakeFiveByteRecord;
  output := callback(input);
  AssertSameFiveByteRecord(input, output);
end;

procedure verify_int_callback_pascal(callback: TIntPascalCallback); cdecl;
var
  output: Integer;
begin
  Assert(Assigned(callback));
  output := callback(41);
  Assert(output = 42);
end;

procedure verify_four_int_callback_register(callback: TFourIntRegisterCallback); cdecl;
var
  output: Integer;
begin
  Assert(Assigned(callback));
  output := callback(0, 1, 2, 3);
  Assert(output = 6);
end;

function verify_mixed_alignment_pascal(a: ShortInt; b: SmallInt; c: LongInt; d: Int64; e: Single; f: Double): LongInt; pascal;
begin
  Result := VerifyMixedAlignmentValues(a, b, c, d, e, f);
end;

function verify_mixed_alignment_register(a: ShortInt; b: SmallInt; c: LongInt; d: Int64; e: Single; f: Double): LongInt; register;
begin
  Result := VerifyMixedAlignmentValues(a, b, c, d, e, f);
end;

procedure verify_mixed_alignment_callback_pascal(callback: TMixedAlignmentPascalCallback); cdecl;
var
  output: LongInt;
begin
  Assert(Assigned(callback));
  output := callback(ShortInt($12), SmallInt($3456), LongInt($12345678), Int64($1122334455667788), Single(16.25), Double(1024.5));
  Assert(output = LongInt($13572468));
end;

procedure verify_mixed_alignment_callback_register(callback: TMixedAlignmentRegisterCallback); cdecl;
var
  output: LongInt;
begin
  Assert(Assigned(callback));
  output := callback(ShortInt($12), SmallInt($3456), LongInt($12345678), Int64($1122334455667788), Single(16.25), Double(1024.5));
  Assert(output = LongInt($13572468));
end;

procedure mutate_large_struct_pascal(input: TFourInt64); pascal;
begin
  input.a := input.a + 1;
  input.b := input.b + 1;
  input.c := input.c + 1;
  input.d := input.d + 1;
end;

procedure mutate_large_struct_register(input: TFourInt64); register;
begin
  input.a := input.a + 1;
  input.b := input.b + 1;
  input.c := input.c + 1;
  input.d := input.d + 1;
end;

exports
  return_struct_cdecl name 'return_struct_cdecl',
  return_struct_pascal name 'return_struct_pascal',
  return_struct_register name 'return_struct_register',
  verify_struct_cdecl name 'verify_struct_cdecl',
  verify_struct_pascal name 'verify_struct_pascal',
  verify_struct_register name 'verify_struct_register',
  identity_cdecl name 'identity_cdecl',
  identity_pascal name 'identity_pascal',
  identity_register name 'identity_register',
  verify_callback_cdecl name 'verify_callback_cdecl',
  verify_callback_pascal name 'verify_callback_pascal',
  verify_callback_register name 'verify_callback_register',
  register_two_args_return_struct name 'register_two_args_return_struct',
  register_three_args_return_struct name 'register_three_args_return_struct',
  register_four_args_return_struct name 'register_four_args_return_struct',
  verify_two_args_callback_register name 'verify_two_args_callback_register',
  verify_three_args_callback_register name 'verify_three_args_callback_register',
  verify_four_args_callback_register name 'verify_four_args_callback_register',
  verify_int_struct_int_pascal name 'verify_int_struct_int_pascal',
  verify_int_struct_int_register name 'verify_int_struct_int_register',
  verify_int_struct_int_callback_pascal name 'verify_int_struct_int_callback_pascal',
  verify_int_struct_int_callback_register name 'verify_int_struct_int_callback_register',
  return_one_integer_struct_pascal name 'return_one_integer_struct_pascal',
  return_one_integer_struct_register name 'return_one_integer_struct_register',
  verify_one_integer_struct_pascal name 'verify_one_integer_struct_pascal',
  verify_one_integer_struct_register name 'verify_one_integer_struct_register',
  verify_two_int_one_integer_struct_pascal name 'verify_two_int_one_integer_struct_pascal',
  verify_two_int_one_integer_struct_register name 'verify_two_int_one_integer_struct_register',
  return_two_int_one_integer_struct_pascal name 'return_two_int_one_integer_struct_pascal',
  return_two_int_one_integer_struct_register name 'return_two_int_one_integer_struct_register',
  verify_int_one_integer_int_pascal name 'verify_int_one_integer_int_pascal',
  verify_int_one_integer_int_register name 'verify_int_one_integer_int_register',
  return_int_one_integer_int_pascal name 'return_int_one_integer_int_pascal',
  return_int_one_integer_int_register name 'return_int_one_integer_int_register',
  verify_one_integer_callback_pascal name 'verify_one_integer_callback_pascal',
  verify_one_integer_callback_register name 'verify_one_integer_callback_register',
  verify_two_int_one_integer_callback_pascal name 'verify_two_int_one_integer_callback_pascal',
  verify_two_int_one_integer_callback_register name 'verify_two_int_one_integer_callback_register',
  verify_int_one_integer_int_callback_pascal name 'verify_int_one_integer_int_callback_pascal',
  verify_int_one_integer_int_callback_register name 'verify_int_one_integer_int_callback_register',
  identity_four_byte_struct_pascal name 'identity_four_byte_struct_pascal',
  identity_four_byte_struct_register name 'identity_four_byte_struct_register',
  identity_five_byte_struct_pascal name 'identity_five_byte_struct_pascal',
  identity_five_byte_struct_register name 'identity_five_byte_struct_register',
  verify_four_byte_callback_pascal name 'verify_four_byte_callback_pascal',
  verify_four_byte_callback_register name 'verify_four_byte_callback_register',
  verify_five_byte_callback_pascal name 'verify_five_byte_callback_pascal',
  verify_five_byte_callback_register name 'verify_five_byte_callback_register',
  verify_int_callback_pascal name 'verify_int_callback_pascal',
  verify_four_int_callback_register name 'verify_four_int_callback_register',
  verify_mixed_alignment_pascal name 'verify_mixed_alignment_pascal',
  verify_mixed_alignment_register name 'verify_mixed_alignment_register',
  verify_mixed_alignment_callback_pascal name 'verify_mixed_alignment_callback_pascal',
  verify_mixed_alignment_callback_register name 'verify_mixed_alignment_callback_register',
  mutate_large_struct_pascal name 'mutate_large_struct_pascal',
  mutate_large_struct_register name 'mutate_large_struct_register';
begin
end.
