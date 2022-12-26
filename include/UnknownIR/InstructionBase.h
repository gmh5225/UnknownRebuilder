#pragma once
#include <UnknownIR/OpCode.h>
#include <UnknownIR/User.h>
#include <UnknownIR/FlagsVariable.h>

#include <UnknownUtils/unknown/Support/raw_ostream.h>
#include <UnknownUtils/unknown/ADT/StringRef.h>

namespace uir {

class BasicBlock;

class Instruction : public User
{
protected:
    OpCodeID mOpCodeID;
    uint64_t mInstructionAddress;
    BasicBlock *mParent;
    FlagsVariable *mFlagsVariable;
    LocalVariable *mStackVariable;
    std::string mExtraInfo;
    std::string mComment;

public:
    Instruction();
    explicit Instruction(OpCodeID OpCodeId);
    virtual ~Instruction();

public:
    // Virtual
    // Get the opcode name of this instruction
    virtual unknown::StringRef getOpcodeName() const;

    // Get the default number of operands
    virtual uint32_t getDefaultNumberOfOperands() const;

    // Is this instruction with flags?
    virtual bool hasFlags() const;

    // Print the instruction
    virtual void print(unknown::raw_ostream &OS) const;

public:
    // Get/Set
    // Get the address of this instruction
    uint64_t getInstructionAddress() const;

    // Set the address of this instruction
    void setInstructionAddress(uint64_t InstructionAddress);

    // Get the parent of this instruction
    const BasicBlock *getParent() const;

    // Get the parent of this instruction
    BasicBlock *getParent();

    // Set the parent of this instruction
    void setParent(BasicBlock *BB);

    // Get the opcode of this instruction
    const OpCodeID getOpCodeID() const;

    // Set the opcode of this instruction
    void setOpCodeID(OpCodeID OpCodeId);

    // Get the flags variable of this instruction
    const FlagsVariable *getFlagsVariable() const;

    // Get the flags variable of this instruction
    FlagsVariable *getFlagsVariable();

    // Set the flags variable of this instruction
    void setFlagsVariable(FlagsVariable *FV);

    // Set the flags variable of this instruction and update its users
    void setFlagsVariableAndUpdateUsers(FlagsVariable *FV);

    // Get the stack variable of this instruction
    const LocalVariable *getStackVariable() const;

    // Get the stack variable of this instruction
    LocalVariable *getStackVariable();

    // Set the stack variable of this instruction
    void setStackVariable(LocalVariable *SV);

    // Set the stack variable of this instruction and update its users
    void setStackVariableAndUpdateUsers(LocalVariable *SV);

    // Get the extra info of this instruction
    const std::string getExtraInfo() const;

    // Set the extra info of this instruction
    void setExtraInfo(unknown::StringRef ExtraInfo);

    // Append the extra info of this instruction
    void appendExtraInfo(unknown::StringRef ExtraInfo);

    // Get the comment of this instruction
    const std::string getComment() const;

    // Set the comment of this instruction
    void setComment(unknown::StringRef Comment);

    // Append the comment of this instruction
    void appendComment(unknown::StringRef Comment);

public:
    // Remove/Erase/Insert/Clear
    // Remove this instruction from its parent, but does not delete it.
    void removeFromParent();

    // Remove this instruction from its parent and delete it.
    void eraseFromParent();

    // Insert an unlinked instructions into a basic block immediately before/after the specified instruction.
    void insertBeforeOrAfter(Instruction *InsertPos, bool Before);

    // Insert an unlinked instructions into a basic block immediately before the specified instruction.
    void insertBefore(Instruction *InsertPos);

    // Insert an unlinked instructions into a basic block immediately after the specified instruction.
    void insertAfter(Instruction *InsertPos);

    // Drop all references to operands.
    void dropAllReferences();

    // Clear all operands in this instruction.
    void clearAllOperands();

public:
    // Static
    static Instruction *get(OpCodeID OpCodeId);
};

class TerminatorInstruction : public Instruction
{
public:
    using SuccessorsListType = std::vector<BasicBlock *>;

protected:
    SuccessorsListType mSuccessorsList;

protected:
    TerminatorInstruction(OpCodeID OpCodeId);
    virtual ~TerminatorInstruction();

public:
    // SuccessorsList
    // Returns the list of successors of this terminator instruction
    SuccessorsListType &getSuccessorsList() { return mSuccessorsList; }
    const SuccessorsListType &getSuccessorsList() const { return mSuccessorsList; }

public:
    // Iterator
    using successor_iterator = SuccessorsListType::iterator;
    using const_successor_iterator = SuccessorsListType::const_iterator;
    successor_iterator successor_begin();
    const_successor_iterator successor_begin() const;
    successor_iterator successor_end();
    const_successor_iterator successor_end() const;
    BasicBlock *successor_back();
    BasicBlock *successor_front();
    void successor_push(BasicBlock *BB);
    void successor_pop();
    size_t successor_count() const;
    void successor_erase(BasicBlock *BB);
    bool successor_empty() const;

public:
    // Get/Set
    // Get the number of successors that this terminator has.
    size_t getNumSuccessors() const;

    // Get the specified successor.
    BasicBlock *getSuccessor(size_t Index) const;

    // Set the specified successor to point at the provided block.
    void setSuccessor(size_t Index, BasicBlock *Successor);

    // Set the specified successor to point at the provided block and update its predecessor.
    void setSuccessorAndUpdatePredecessor(size_t Index, BasicBlock *Successor);

    // Insert a new successor into the terminator instruction.
    void insertSuccessor(BasicBlock *Successor);

    // Erase a successor into the terminator instruction.
    void eraseSuccessor(BasicBlock *Successor);
};

} // namespace uir
