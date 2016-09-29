// ----- ----- Class 1: Libio ----- -----

package include;

public class Libio {
	public final static int EOF = -1;
}


// ----- ----- Class 2: DemoTranslation ----- -----

package demo;

import static com.mtsystems.coot.String8.cs8;
import static com.mtsystems.coot.String8.s8;
import static implicit_code.ImplicitDeclarations.fprint;
import static implicit_code.ImplicitDeclarations.fscan;
import static include.Libio.EOF;
import static include.Stdio.fclose;
import static include.Stdio.fopen;
import static include.Stdio.fprintf;
import static include.Stdio.sscanf;

import com.mtsystems.coot.Container;
import com.mtsystems.coot.IntContainer;
import com.mtsystems.coot.MethodRef0;
import com.mtsystems.coot.String8;

import implicit_code.ImplicitDeclarations;

import include.IoFile;

public class DemoTranslation {
	public final static boolean DEBUG = false;

	public final static String8 USAGE = cs8("usage: incre N file");

	public static int main(int argc, String8[] argv) {
		IntContainer n = new IntContainer(1), i = new IntContainer(1);
		int rv;
		Container<IoFile> f;
		if(argc < 3) {
			System.out.println("\n" + USAGE);
			System.out.println("N is # iter\n file is filename wi #");
			return 1;
		}
		if(DEBUG) {
			System.out.println("..looking for N");
		}
		if(sscanf(argv[1], cs8("%d"), n) != 1) {
			System.out.println("sscanf failed on # of iters");
			return 1;
		}
		if(DEBUG) {
			System.out.println("N is " + n.get());
		}
		if(n.get() <= 0) {
			System.out.println("bad N: " + argv[1]);
			return 1;
		}

		if(DEBUG) {
			System.out.println("..looking for filename");
		}

		if(DEBUG) {
			System.out.println("filename is " + argv[2]);
		}
		while(n.get() > 0) {
			if(null == (f = fopen(argv[2], cs8("r+")))) {
				System.out.println("bad file: " + argv[2]);
				return 1;
			}
			if(DEBUG) {
				System.out.println("..working on iter " + n.get());
			}
			while((rv = fscan(f, cs8("%d"), i)) != EOF) {
				if(DEBUG) {
					System.out.println(i.get());
				}
				if((rv = 0) != 0) {
					fprint((MethodRef0<Integer>)ImplicitDeclarations::srderr, cs8("File has non-#\n"));
					return 1;
				}
			}
			if(DEBUG) {
				System.out.println("Last i= " + i.get());
			}
			i.set(i.get() + 1);
			if(DEBUG) {
				System.out.println("new i= " + i.get());
			}
			fprintf(f, cs8("%d\n"), i.get());
			n.set(n.get() - 1);
			fclose(f);
		}
		System.out.println();
		return 0;
	}

	public static void main(String[] args) {
		String8[] cArgs = new String8[args.length + 1];
		cArgs[0] = s8(DemoTranslation.class.getSimpleName());
		for(int i = 0; i < args.length; i++) {
			cArgs[i + 1] = s8(args[i]);
		}
		int ret = main(cArgs.length, cArgs);
		if(ret != 0) {
			System.exit(ret);
		}
	}
}


// ----- ----- Class 3: ImplicitDeclarations ----- -----

package implicit_code;

import com.mtsystems.coot.NativeHelper;

public class ImplicitDeclarations {
	static {
		// The online demo uses the example library "libc.so.6".
		// Have a look at the translated programs for real values.
		NativeHelper h = NativeHelper.get("libc.so.6");
		h.bindDirect(ImplicitDeclarations.class);
	}

	public static native int srderr();

	public static native int fprint();

	public static native int fscan();
}


// ----- ----- Class 4: IoMarker ----- -----

package include;

import com.mtsystems.coot.Container;
import com.mtsystems.coot.IntContainer;
import com.mtsystems.coot.NativeClass;

/**
 * A streammarker remembers a position in a buffer.
 */
public class IoMarker extends NativeClass {
	private final Container<Container<IoMarker>> next = new Container<Container<IoMarker>>(this, 1){};

	/**
	 * If _pos >= 0
	 * it points to _buf->Gbase()+_pos. FIXME comment
	 */
	private final Container<Container<IoFile>> sbuf = new Container<Container<IoFile>>(this, 1){};

	/**
	 * if _pos < 0, it points to _buf->eBptr()+_pos. FIXME comment
	 */
	private final IntContainer pos = new IntContainer(this, 1);

	public Container<IoMarker> getNext() {
		return next.get();
	}

	public Container<IoMarker> setNext(Container<IoMarker> newNext) {
		return next.set(newNext);
	}

	public Container<IoFile> getSbuf() {
		return sbuf.get();
	}

	public Container<IoFile> setSbuf(Container<IoFile> newSbuf) {
		return sbuf.set(newSbuf);
	}

	public int getPos() {
		return pos.get();
	}

	public int setPos(int newPos) {
		return pos.set(newPos);
	}
}


// ----- ----- Class 5: IoFile ----- -----

package include;

import static com.mtsystems.coot.NativeInformation.INT_SIZE;
import static com.mtsystems.coot.NativeInformation.LONG_SIZE;
import static com.mtsystems.coot.NativeInformation.POINTER_SIZE;

import com.mtsystems.coot.AbstractData;
import com.mtsystems.coot.Container;
import com.mtsystems.coot.IntContainer;
import com.mtsystems.coot.LongContainer;
import com.mtsystems.coot.NativeClass;
import com.mtsystems.coot.ShortContainer;
import com.mtsystems.coot.String8;

public class IoFile extends NativeClass {
	/**
	 * High-order word is _IO_MAGIC; rest is flags.
	 */
	private final IntContainer flags = new IntContainer(this, 1);

	/**
	 * Note:  Tk uses the _IO_read_ptr and _IO_read_end fields directly.
	 *
	 * Current read pointer
	 */
	private final Container<String8> ioReadPtr = new Container<String8>(this, 1){};

	/**
	 * End of get area.
	 */
	private final Container<String8> ioReadEnd = new Container<String8>(this, 1){};

	/**
	 * Start of putback+get area.
	 */
	private final Container<String8> ioReadBase = new Container<String8>(this, 1){};

	/**
	 * Start of put area.
	 */
	private final Container<String8> ioWriteBase = new Container<String8>(this, 1){};

	/**
	 * Current put pointer.
	 */
	private final Container<String8> ioWritePtr = new Container<String8>(this, 1){};

	/**
	 * End of put area.
	 */
	private final Container<String8> ioWriteEnd = new Container<String8>(this, 1){};

	/**
	 * Start of reserve area.
	 */
	private final Container<String8> ioBufBase = new Container<String8>(this, 1){};

	/**
	 * End of reserve area.
	 */
	private final Container<String8> ioBufEnd = new Container<String8>(this, 1){};

	/**
	 * The following fields are used to support backing up and undo.
	 *
	 * Pointer to start of non-current get area.
	 */
	private final Container<String8> ioSaveBase = new Container<String8>(this, 1){};

	/**
	 * Pointer to first valid character of backup area
	 */
	private final Container<String8> ioBackupBase = new Container<String8>(this, 1){};

	/**
	 * Pointer to end of non-current get area.
	 */
	private final Container<String8> ioSaveEnd = new Container<String8>(this, 1){};

	private final Container<Container<IoMarker>> markers = new Container<Container<IoMarker>>(this, 1){};

	private final Container<Container<IoFile>> chain = new Container<Container<IoFile>>(this, 1){};

	private final IntContainer fileno = new IntContainer(this, 1);

	private final IntContainer flags2 = new IntContainer(this, 1);

	/**
	 * This used to be _offset but it's too small.
	 */
	private final LongContainer oldOffset = new LongContainer(this, 1);

	/**
	 * 1+column number of pbase(); 0 is unknown.
	 */
	private final ShortContainer curColumn_U = new ShortContainer(this, 1);

	private final String8 vtableOffset = new String8(this, 1);

	private final String8 shortbuf = new String8(this, 1);

	/**
	 * char* _save_gptr;  char* _save_egptr;
	 */
	private final Container<AbstractData> lock = new Container<AbstractData>(this, 1){};

	private final LongContainer offset = new LongContainer(this, 1);

	private final Container<AbstractData> pad1 = new Container<AbstractData>(this, 1){};

	private final Container<AbstractData> pad2 = new Container<AbstractData>(this, 1){};

	private final Container<AbstractData> pad3 = new Container<AbstractData>(this, 1){};

	private final Container<AbstractData> pad4 = new Container<AbstractData>(this, 1){};

	private final LongContainer pad5_U = new LongContainer(this, 1);

	private final IntContainer mode = new IntContainer(this, 1);

	/**
	 * Make sure we don't get into trouble again.
	 */
	private final String8 unused2 = new String8(this, (int)(15 * ((long)INT_SIZE) - 4 * ((long)POINTER_SIZE) - ((long)LONG_SIZE)));

	public int getFlags() {
		return flags.get();
	}

	public int setFlags(int newFlags) {
		return flags.set(newFlags);
	}

	public String8 getIoReadPtr() {
		return ioReadPtr.get();
	}

	public String8 setIoReadPtr(String8 newIoReadPtr) {
		return ioReadPtr.set(newIoReadPtr);
	}

	public String8 getIoReadEnd() {
		return ioReadEnd.get();
	}

	public String8 setIoReadEnd(String8 newIoReadEnd) {
		return ioReadEnd.set(newIoReadEnd);
	}

	public String8 getIoReadBase() {
		return ioReadBase.get();
	}

	public String8 setIoReadBase(String8 newIoReadBase) {
		return ioReadBase.set(newIoReadBase);
	}

	public String8 getIoWriteBase() {
		return ioWriteBase.get();
	}

	public String8 setIoWriteBase(String8 newIoWriteBase) {
		return ioWriteBase.set(newIoWriteBase);
	}

	public String8 getIoWritePtr() {
		return ioWritePtr.get();
	}

	public String8 setIoWritePtr(String8 newIoWritePtr) {
		return ioWritePtr.set(newIoWritePtr);
	}

	public String8 getIoWriteEnd() {
		return ioWriteEnd.get();
	}

	public String8 setIoWriteEnd(String8 newIoWriteEnd) {
		return ioWriteEnd.set(newIoWriteEnd);
	}

	public String8 getIoBufBase() {
		return ioBufBase.get();
	}

	public String8 setIoBufBase(String8 newIoBufBase) {
		return ioBufBase.set(newIoBufBase);
	}

	public String8 getIoBufEnd() {
		return ioBufEnd.get();
	}

	public String8 setIoBufEnd(String8 newIoBufEnd) {
		return ioBufEnd.set(newIoBufEnd);
	}

	public String8 getIoSaveBase() {
		return ioSaveBase.get();
	}

	public String8 setIoSaveBase(String8 newIoSaveBase) {
		return ioSaveBase.set(newIoSaveBase);
	}

	public String8 getIoBackupBase() {
		return ioBackupBase.get();
	}

	public String8 setIoBackupBase(String8 newIoBackupBase) {
		return ioBackupBase.set(newIoBackupBase);
	}

	public String8 getIoSaveEnd() {
		return ioSaveEnd.get();
	}

	public String8 setIoSaveEnd(String8 newIoSaveEnd) {
		return ioSaveEnd.set(newIoSaveEnd);
	}

	public Container<IoMarker> getMarkers() {
		return markers.get();
	}

	public Container<IoMarker> setMarkers(Container<IoMarker> newMarkers) {
		return markers.set(newMarkers);
	}

	public Container<IoFile> getChain() {
		return chain.get();
	}

	public Container<IoFile> setChain(Container<IoFile> newChain) {
		return chain.set(newChain);
	}

	public int getFileno() {
		return fileno.get();
	}

	public int setFileno(int newFileno) {
		return fileno.set(newFileno);
	}

	public int getFlags2() {
		return flags2.get();
	}

	public int setFlags2(int newFlags2) {
		return flags2.set(newFlags2);
	}

	public long getOldOffset() {
		return oldOffset.get();
	}

	public long setOldOffset(long newOldOffset) {
		return oldOffset.set(newOldOffset);
	}

	public short getCurColumn_U() {
		return curColumn_U.get();
	}

	public short setCurColumn_U(short newCurColumn_U) {
		return curColumn_U.set(newCurColumn_U);
	}

	public byte getVtableOffset() {
		return vtableOffset.get();
	}

	public byte setVtableOffset(byte newVtableOffset) {
		return vtableOffset.set(newVtableOffset);
	}

	public String8 getShortbuf() {
		return shortbuf;
	}

	public AbstractData getLock() {
		return lock.get();
	}

	public AbstractData setLock(AbstractData newLock) {
		return lock.set(newLock);
	}

	public long getOffset() {
		return offset.get();
	}

	public long setOffset(long newOffset) {
		return offset.set(newOffset);
	}

	public AbstractData getPad1() {
		return pad1.get();
	}

	public AbstractData setPad1(AbstractData newPad1) {
		return pad1.set(newPad1);
	}

	public AbstractData getPad2() {
		return pad2.get();
	}

	public AbstractData setPad2(AbstractData newPad2) {
		return pad2.set(newPad2);
	}

	public AbstractData getPad3() {
		return pad3.get();
	}

	public AbstractData setPad3(AbstractData newPad3) {
		return pad3.set(newPad3);
	}

	public AbstractData getPad4() {
		return pad4.get();
	}

	public AbstractData setPad4(AbstractData newPad4) {
		return pad4.set(newPad4);
	}

	public long getPad5_U() {
		return pad5_U.get();
	}

	public long setPad5_U(long newPad5_U) {
		return pad5_U.set(newPad5_U);
	}

	public int getMode() {
		return mode.get();
	}

	public int setMode(int newMode) {
		return mode.set(newMode);
	}

	public String8 getUnused2() {
		return unused2;
	}
}


// ----- ----- Class 6: Stdio ----- -----

package include;

import com.mtsystems.coot.Container;
import com.mtsystems.coot.NativeHelper;
import com.mtsystems.coot.String8;
import com.sun.jna.Library;

public class Stdio {
	private static interface IndirectMappings extends Library {
		int fprintf(Container<IoFile> stream, String8 format, Object... varargs);

		int sscanf(String8 s, String8 format, Object... varargs);
	}

	private final static IndirectMappings INDIRECT_MAPPINGS;

	static {
		// The online demo uses the example library "libc.so.6".
		// Have a look at the translated programs for real values.
		NativeHelper h = NativeHelper.get("libc.so.6");
		h.bindDirect(Stdio.class);
		INDIRECT_MAPPINGS = h.bindIndirect(IndirectMappings.class);
	}

	/**
	 * Close STREAM.
	 */
	public static native int fclose(Container<IoFile> stream);

	/**
	 * Open a file and create a new stream for it.
	 */
	public static native Container<IoFile> fopen(String8 filename, String8 modes);

	/**
	 * Write formatted output to STREAM.
	 */
	public static int fprintf(Container<IoFile> stream, String8 format, Object... varargs) {
		return INDIRECT_MAPPINGS.fprintf(stream, format, varargs);
	}

	/**
	 * Read formatted input from S.
	 */
	public static int sscanf(String8 s, String8 format, Object... varargs) {
		return INDIRECT_MAPPINGS.sscanf(s, format, varargs);
	}
}