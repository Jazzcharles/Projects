VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   6765
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   8760
   LinkTopic       =   "Form1"
   ScaleHeight     =   9601.479
   ScaleMode       =   0  'User
   ScaleWidth      =   11349.8
   StartUpPosition =   3  '¥∞ø⁄»± °
   Begin VB.PictureBox Picture1 
      Height          =   495
      Index           =   0
      Left            =   720
      ScaleHeight     =   435
      ScaleWidth      =   555
      TabIndex        =   0
      Top             =   360
      Width           =   615
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim tile, sz, x, y, tot As Integer


Private Sub chessboard(ByVal tr%, ByVal tc%, ByVal dr%, ByVal dc%, ByVal size%)
    If size = 1 Then
        Exit Sub
    End If
    Dim col, red, green, blue As Integer
    Randomize
    red = Int(Rnd * 255)
    green = Int(Rnd * 255)
    blue = Int(Rnd * 255)
    
    col = RGB(red, green, blue)
    'Debug.Print col
    
    Dim t As Integer
        t = tile
        tile = tile + 1
    Dim s As Integer
        s = size / 2
        
        
    'Debug.Print t, s
    
    '∏≤∏«◊Û…œΩ«∆Â≈Ã
    If dr < tr + s And dc < tc + s Then
        chessboard tr, tc, dr, dc, s
    Else
    '◊Û…œΩ«√ª”–µƒª∞∏≤∏«”“œ¬Ω«
        r = tr + s - 1
        c = tc + s - 1
        Picture1(r * sz + c).BackColor = col
        Picture1(r * sz + c).AutoRedraw = True
        Picture1(r * sz + c).FontSize = 160 / sz
        Picture1(r * sz + c).Print t
        chessboard tr, tc, tr + s - 1, tc + s - 1, s
    End If
    
    '”“…œΩ«
    If dr < tr + s And dc >= tc + s Then
        chessboard tr, tc + s, dr, dc, s
    Else
        r = tr + s - 1
        c = tc + s
        Picture1(r * sz + c).BackColor = col
        Picture1(r * sz + c).AutoRedraw = True
        Picture1(r * sz + c).FontSize = 160 / sz
        Picture1(r * sz + c).Print t
        chessboard tr, tc + s, tr + s - 1, tc + s, s
    End If
    
    '◊Ûœ¬Ω«
    If dr >= tr + s And dc < tc + s Then
        chessboard tr + s, tc, dr, dc, s
    Else
        r = tr + s
        c = tc + s - 1
        Picture1(r * sz + c).BackColor = col
        Picture1(r * sz + c).AutoRedraw = True
        Picture1(r * sz + c).FontSize = 160 / sz
        Picture1(r * sz + c).Print t
        chessboard tr + s, tc, tr + s, tc + s - 1, s
    End If
    
    '”“œ¬Ω«
    If dr >= tr + s And dc >= tc + s Then
        chessboard tr + s, tc + s, dr, dc, s
    Else
        r = tr + s
        c = tc + s
        Picture1(r * sz + c).BackColor = col
        Picture1(r * sz + c).AutoRedraw = True
        Picture1(r * sz + c).FontSize = 160 / sz
        Picture1(r * sz + c).Print t
        chessboard tr + s, tc + s, tr + s, tc + s, s
    End If
    
    
End Sub



Private Sub Form_Load()
    sz = InputBox("Please input the size of the chessboard", "Justice rains from above")
    x = InputBox("Please input the x-coordinate of the special box", "Justice rains from above")
    y = InputBox("Please input the y-coordinate of the special box", "Justice rains from above")
    tot = sz * sz
    Dim i As Integer
    
    For i = 1 To tot
        Load Picture1(i)
    Next i
    
    For i = 0 To tot - 1
        Picture1(i).Width = ScaleWidth / sz
        Picture1(i).Height = ScaleHeight / sz
        If i < sz Then
            Picture1(i).Top = 0
        Else
            Picture1(i).Top = Picture1(i - sz).Top + Picture1(i - sz).Height
        End If
        
        If (i Mod sz) = 0 Then
            Picture1(i).Left = 0
        Else
            Picture1(i).Left = Picture1(i - 1).Left + Picture1(i).Width
        End If
        
        Picture1(i).Visible = True
        Picture1(i).BorderStyle = 1
    Next i
    
        
        
    For i = 0 To tot - 1
        Picture1(i).BackColor = RGB(255, 255, 255)
    Next i
    
    tile = 1
    Picture1(x * sz + y).BackColor = RGB(0, 0, 0)
    chessboard 0, 0, x, y, sz
End Sub
