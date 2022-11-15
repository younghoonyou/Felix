const InputName = (props) => {
  const { title, type, name, value, onChange, pre } = props;

  return (
    <>
      <label className='Input-name' htmlFor={title}>
        {title.toUpperCase()}
      </label>
      <input
        type={type ?? title}
        name={name ?? title}
        value={value}
        onChange={onChange}
        placeholder={pre}
        className='Input-Inputs'
      />
    </>
  );
};

export default InputName;
