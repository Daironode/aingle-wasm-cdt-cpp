(module
  (type (;0;) (func))
  (type (;1;) (func (param i32 i32)))
  (type (;2;) (func (param i32 i32 i32 i32 i32) (result i32)))
  (import "env" "aingle_return" (func (;0;) (type 1)))
  (import "env" "aingle_storage_read" (func (;1;) (type 2)))
  (func (;2;) (type 0)
	i32.const 0  ;; storge offset
	i32.const 35;; init key 0x23(KEY_MIGRATE_STORE)
	i32.store8   ;; store key
	i32.const 0  ;; key addr
	i32.const 1  ;; key size 1 byte
	i32.const 8  ;; data addr
	i32.const 8  ;; data is i64
	i32.const 0  ;; always 0
	call 1		 ;; read key to data addr of data size
	i32.const 8  ;; should read 8
	i32.ne
	if
		unreachable ;; if read length not 8 will panic
	end
	i32.const 8  ;; data addr
	i32.const 8  ;; data is i64
	call 0		 ;; return
	)
  (memory (;0;) 1)
  (export "invoke" (func 2)))
