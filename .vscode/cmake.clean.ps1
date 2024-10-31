git clean -dfX
$tdc="$PSScriptRoot/../"
do {
  $dirs = gci $tdc -directory -recurse | Where { (gci $_.fullName).count -eq 0 } | select -expandproperty FullName
  $dirs | Foreach-Object { Remove-Item $_ -Recurse -Force }
} while ($dirs.count -gt 0)